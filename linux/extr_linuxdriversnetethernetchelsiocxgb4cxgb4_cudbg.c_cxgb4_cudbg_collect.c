#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cudbg_init {int outbuf_size; scalar_t__ compress_type; void* outbuf; struct adapter* adap; } ;
struct cudbg_hdr {int hdr_len; int max_entities; scalar_t__ compress_type; int data_len; int /*<<< orphan*/  dump_type; int /*<<< orphan*/  chip_ver; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  major_ver; int /*<<< orphan*/  signature; } ;
struct cudbg_entity_hdr {int dummy; } ;
struct cudbg_buffer {int size; int offset; void* data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ CUDBG_COMPRESSION_NONE ; 
 scalar_t__ CUDBG_COMPRESSION_ZLIB ; 
 int /*<<< orphan*/  CUDBG_DUMP_TYPE_MINI ; 
 int /*<<< orphan*/  CUDBG_MAJOR_VERSION ; 
 int CUDBG_MAX_ENTITY ; 
 int /*<<< orphan*/  CUDBG_MINOR_VERSION ; 
 int /*<<< orphan*/  CUDBG_SIGNATURE ; 
 int CXGB4_ETH_DUMP_HW ; 
 int CXGB4_ETH_DUMP_MEM ; 
 int ENOMEM ; 
 int cudbg_alloc_compress_buff (struct cudbg_init*) ; 
 int /*<<< orphan*/  cudbg_free_compress_buff (struct cudbg_init*) ; 
 int cudbg_get_workspace_size () ; 
 int /*<<< orphan*/  cxgb4_collect_hw_dump ; 
 int /*<<< orphan*/  cxgb4_collect_mem_dump ; 
 int /*<<< orphan*/  cxgb4_cudbg_collect_entity (struct cudbg_init*,struct cudbg_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct cudbg_init*,int /*<<< orphan*/ ,int) ; 

int cxgb4_cudbg_collect(struct adapter *adap, void *buf, u32 *buf_size,
			u32 flag)
{
	struct cudbg_buffer dbg_buff = { 0 };
	u32 size, min_size, total_size = 0;
	struct cudbg_init cudbg_init;
	struct cudbg_hdr *cudbg_hdr;
	int rc;

	size = *buf_size;

	memset(&cudbg_init, 0, sizeof(struct cudbg_init));
	cudbg_init.adap = adap;
	cudbg_init.outbuf = buf;
	cudbg_init.outbuf_size = size;

	dbg_buff.data = buf;
	dbg_buff.size = size;
	dbg_buff.offset = 0;

	cudbg_hdr = (struct cudbg_hdr *)buf;
	cudbg_hdr->signature = CUDBG_SIGNATURE;
	cudbg_hdr->hdr_len = sizeof(struct cudbg_hdr);
	cudbg_hdr->major_ver = CUDBG_MAJOR_VERSION;
	cudbg_hdr->minor_ver = CUDBG_MINOR_VERSION;
	cudbg_hdr->max_entities = CUDBG_MAX_ENTITY;
	cudbg_hdr->chip_ver = adap->params.chip;
	cudbg_hdr->dump_type = CUDBG_DUMP_TYPE_MINI;

	min_size = sizeof(struct cudbg_hdr) +
		   sizeof(struct cudbg_entity_hdr) *
		   cudbg_hdr->max_entities;
	if (size < min_size)
		return -ENOMEM;

	rc = cudbg_get_workspace_size();
	if (rc) {
		/* Zlib available.  So, use zlib deflate */
		cudbg_init.compress_type = CUDBG_COMPRESSION_ZLIB;
		rc = cudbg_alloc_compress_buff(&cudbg_init);
		if (rc) {
			/* Ignore error and continue without compression. */
			dev_warn(adap->pdev_dev,
				 "Fail allocating compression buffer ret: %d.  Continuing without compression.\n",
				 rc);
			cudbg_init.compress_type = CUDBG_COMPRESSION_NONE;
			rc = 0;
		}
	} else {
		cudbg_init.compress_type = CUDBG_COMPRESSION_NONE;
	}

	cudbg_hdr->compress_type = cudbg_init.compress_type;
	dbg_buff.offset += min_size;
	total_size = dbg_buff.offset;

	if (flag & CXGB4_ETH_DUMP_HW)
		cxgb4_cudbg_collect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_collect_hw_dump,
					   ARRAY_SIZE(cxgb4_collect_hw_dump),
					   buf,
					   &total_size);

	if (flag & CXGB4_ETH_DUMP_MEM)
		cxgb4_cudbg_collect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_collect_mem_dump,
					   ARRAY_SIZE(cxgb4_collect_mem_dump),
					   buf,
					   &total_size);

	cudbg_free_compress_buff(&cudbg_init);
	cudbg_hdr->data_len = total_size;
	if (cudbg_init.compress_type != CUDBG_COMPRESSION_NONE)
		*buf_size = size;
	else
		*buf_size = total_size;
	return 0;
}