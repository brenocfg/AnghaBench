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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_transport_mw {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/ * alloc_addr; scalar_t__ alloc_size; scalar_t__ buff_size; scalar_t__ xlat_size; int /*<<< orphan*/  dma_addr; } ;
struct ntb_transport_ctx {TYPE_1__* ndev; struct ntb_transport_mw* mw_vec; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDX ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_mw_clear_trans (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ntb_free_mw(struct ntb_transport_ctx *nt, int num_mw)
{
	struct ntb_transport_mw *mw = &nt->mw_vec[num_mw];
	struct pci_dev *pdev = nt->ndev->pdev;

	if (!mw->virt_addr)
		return;

	ntb_mw_clear_trans(nt->ndev, PIDX, num_mw);
	dma_free_coherent(&pdev->dev, mw->alloc_size,
			  mw->alloc_addr, mw->dma_addr);
	mw->xlat_size = 0;
	mw->buff_size = 0;
	mw->alloc_size = 0;
	mw->alloc_addr = NULL;
	mw->virt_addr = NULL;
}