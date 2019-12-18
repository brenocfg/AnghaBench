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
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {int /*<<< orphan*/  internalbufs; struct venus_core* core; } ;
struct venus_core {struct device* dev; } ;
struct intbuf {int attrs; int /*<<< orphan*/  da; int /*<<< orphan*/  va; scalar_t__ size; int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;
struct hfi_buffer_requirements {unsigned int count_actual; scalar_t__ size; int /*<<< orphan*/  type; } ;
struct hfi_buffer_desc {int num_buffers; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  buffer_type; scalar_t__ buffer_size; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  bd ;

/* Variables and functions */
 int DMA_ATTR_NO_KERNEL_MAPPING ; 
 int DMA_ATTR_WRITE_COMBINE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_alloc_attrs (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_free_attrs (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hfi_session_set_buffers (struct venus_inst*,struct hfi_buffer_desc*) ; 
 int /*<<< orphan*/  kfree (struct intbuf*) ; 
 struct intbuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hfi_buffer_desc*,int /*<<< orphan*/ ,int) ; 
 int venus_helper_get_bufreq (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_buffer_requirements*) ; 

__attribute__((used)) static int intbufs_set_buffer(struct venus_inst *inst, u32 type)
{
	struct venus_core *core = inst->core;
	struct device *dev = core->dev;
	struct hfi_buffer_requirements bufreq;
	struct hfi_buffer_desc bd;
	struct intbuf *buf;
	unsigned int i;
	int ret;

	ret = venus_helper_get_bufreq(inst, type, &bufreq);
	if (ret)
		return 0;

	if (!bufreq.size)
		return 0;

	for (i = 0; i < bufreq.count_actual; i++) {
		buf = kzalloc(sizeof(*buf), GFP_KERNEL);
		if (!buf) {
			ret = -ENOMEM;
			goto fail;
		}

		buf->type = bufreq.type;
		buf->size = bufreq.size;
		buf->attrs = DMA_ATTR_WRITE_COMBINE |
			     DMA_ATTR_NO_KERNEL_MAPPING;
		buf->va = dma_alloc_attrs(dev, buf->size, &buf->da, GFP_KERNEL,
					  buf->attrs);
		if (!buf->va) {
			ret = -ENOMEM;
			goto fail;
		}

		memset(&bd, 0, sizeof(bd));
		bd.buffer_size = buf->size;
		bd.buffer_type = buf->type;
		bd.num_buffers = 1;
		bd.device_addr = buf->da;

		ret = hfi_session_set_buffers(inst, &bd);
		if (ret) {
			dev_err(dev, "set session buffers failed\n");
			goto dma_free;
		}

		list_add_tail(&buf->list, &inst->internalbufs);
	}

	return 0;

dma_free:
	dma_free_attrs(dev, buf->size, buf->va, buf->da, buf->attrs);
fail:
	kfree(buf);
	return ret;
}