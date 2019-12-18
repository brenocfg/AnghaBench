#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vpdma_data {TYPE_1__* pdev; int /*<<< orphan*/  (* cb ) (TYPE_1__*) ;} ;
struct vpdma_buf {scalar_t__ dma_addr; int /*<<< orphan*/  addr; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPDMA_LIST_ADDR ; 
 int /*<<< orphan*/  VPDMA_LIST_ATTR ; 
 int /*<<< orphan*/  VPDMA_LIST_RDY_MASK ; 
 int /*<<< orphan*/  VPDMA_LIST_RDY_SHFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ read_field_reg (struct vpdma_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int vpdma_alloc_desc_buf (struct vpdma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpdma_free_desc_buf (struct vpdma_buf*) ; 
 int /*<<< orphan*/  vpdma_map_desc_buf (struct vpdma_data*,struct vpdma_buf*) ; 
 int /*<<< orphan*/  vpdma_unmap_desc_buf (struct vpdma_data*,struct vpdma_buf*) ; 
 int /*<<< orphan*/  write_reg (struct vpdma_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpdma_firmware_cb(const struct firmware *f, void *context)
{
	struct vpdma_data *vpdma = context;
	struct vpdma_buf fw_dma_buf;
	int i, r;

	dev_dbg(&vpdma->pdev->dev, "firmware callback\n");

	if (!f || !f->data) {
		dev_err(&vpdma->pdev->dev, "couldn't get firmware\n");
		return;
	}

	/* already initialized */
	if (read_field_reg(vpdma, VPDMA_LIST_ATTR, VPDMA_LIST_RDY_MASK,
			VPDMA_LIST_RDY_SHFT)) {
		vpdma->cb(vpdma->pdev);
		return;
	}

	r = vpdma_alloc_desc_buf(&fw_dma_buf, f->size);
	if (r) {
		dev_err(&vpdma->pdev->dev,
			"failed to allocate dma buffer for firmware\n");
		goto rel_fw;
	}

	memcpy(fw_dma_buf.addr, f->data, f->size);

	vpdma_map_desc_buf(vpdma, &fw_dma_buf);

	write_reg(vpdma, VPDMA_LIST_ADDR, (u32) fw_dma_buf.dma_addr);

	for (i = 0; i < 100; i++) {		/* max 1 second */
		msleep_interruptible(10);

		if (read_field_reg(vpdma, VPDMA_LIST_ATTR, VPDMA_LIST_RDY_MASK,
				VPDMA_LIST_RDY_SHFT))
			break;
	}

	if (i == 100) {
		dev_err(&vpdma->pdev->dev, "firmware upload failed\n");
		goto free_buf;
	}

	vpdma->cb(vpdma->pdev);

free_buf:
	vpdma_unmap_desc_buf(vpdma, &fw_dma_buf);

	vpdma_free_desc_buf(&fw_dma_buf);
rel_fw:
	release_firmware(f);
}