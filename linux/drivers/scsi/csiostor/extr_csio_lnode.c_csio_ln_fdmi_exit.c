#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct csio_lnode {TYPE_2__* mgmt_req; } ;
struct csio_hw {TYPE_1__* pdev; } ;
struct csio_dma_buf {int /*<<< orphan*/  paddr; scalar_t__ vaddr; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {struct csio_dma_buf dma_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static int
csio_ln_fdmi_exit(struct csio_lnode *ln)
{
	struct csio_dma_buf *dma_buf;
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	if (!ln->mgmt_req)
		return 0;

	dma_buf = &ln->mgmt_req->dma_buf;
	if (dma_buf->vaddr)
		dma_free_coherent(&hw->pdev->dev, dma_buf->len, dma_buf->vaddr,
				    dma_buf->paddr);

	kfree(ln->mgmt_req);
	return 0;
}