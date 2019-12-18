#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct srp_indirect_buf {int /*<<< orphan*/  len; } ;
struct srp_direct_buf {int /*<<< orphan*/  len; } ;
struct srp_cmd {int buf_fmt; int add_cdb_len; int /*<<< orphan*/ * add_data; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int SRP_DATA_DESC_DIRECT ; 
 int SRP_DATA_DESC_INDIRECT ; 
 int /*<<< orphan*/  __same_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

int srp_get_desc_table(struct srp_cmd *srp_cmd, enum dma_data_direction *dir,
		       u64 *data_len)
{
	struct srp_indirect_buf *idb;
	struct srp_direct_buf *db;
	uint add_cdb_offset;
	int rc;

	/*
	 * The pointer computations below will only be compiled correctly
	 * if srp_cmd::add_data is declared as s8*, u8*, s8[] or u8[], so check
	 * whether srp_cmd::add_data has been declared as a byte pointer.
	 */
	BUILD_BUG_ON(!__same_type(srp_cmd->add_data[0], (s8)0)
		     && !__same_type(srp_cmd->add_data[0], (u8)0));

	BUG_ON(!dir);
	BUG_ON(!data_len);

	rc = 0;
	*data_len = 0;

	*dir = DMA_NONE;

	if (srp_cmd->buf_fmt & 0xf)
		*dir = DMA_FROM_DEVICE;
	else if (srp_cmd->buf_fmt >> 4)
		*dir = DMA_TO_DEVICE;

	add_cdb_offset = srp_cmd->add_cdb_len & ~3;
	if (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_DIRECT) ||
	    ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_DIRECT)) {
		db = (struct srp_direct_buf *)(srp_cmd->add_data
					       + add_cdb_offset);
		*data_len = be32_to_cpu(db->len);
	} else if (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_INDIRECT) ||
		   ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_INDIRECT)) {
		idb = (struct srp_indirect_buf *)(srp_cmd->add_data
						  + add_cdb_offset);

		*data_len = be32_to_cpu(idb->len);
	}
	return rc;
}