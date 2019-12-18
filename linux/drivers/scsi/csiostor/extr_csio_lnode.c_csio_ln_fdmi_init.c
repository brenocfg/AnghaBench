#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct csio_lnode {int /*<<< orphan*/  flags; TYPE_2__* mgmt_req; } ;
struct csio_ioreq {int dummy; } ;
struct csio_hw {TYPE_1__* pdev; } ;
struct csio_dma_buf {int len; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_5__ {struct csio_dma_buf dma_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_LNF_FDMI_ENABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_ln_fdmi_init(struct csio_lnode *ln)
{
	struct csio_hw *hw = csio_lnode_to_hw(ln);
	struct csio_dma_buf	*dma_buf;

	/* Allocate MGMT request required for FDMI */
	ln->mgmt_req = kzalloc(sizeof(struct csio_ioreq), GFP_KERNEL);
	if (!ln->mgmt_req) {
		csio_ln_err(ln, "Failed to alloc ioreq for FDMI\n");
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/* Allocate Dma buffers for FDMI response Payload */
	dma_buf = &ln->mgmt_req->dma_buf;
	dma_buf->len = 2048;
	dma_buf->vaddr = dma_alloc_coherent(&hw->pdev->dev, dma_buf->len,
						&dma_buf->paddr, GFP_KERNEL);
	if (!dma_buf->vaddr) {
		csio_err(hw, "Failed to alloc DMA buffer for FDMI!\n");
		kfree(ln->mgmt_req);
		ln->mgmt_req = NULL;
		return -ENOMEM;
	}

	ln->flags |= CSIO_LNF_FDMI_ENABLE;
	return 0;
}