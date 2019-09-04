#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hw_dma {int /*<<< orphan*/  size; int /*<<< orphan*/  mapping; int /*<<< orphan*/  addr; } ;
struct bnx2x {TYPE_1__* vfdb; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mapping; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_2__ sp_dma; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mapping; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mapping; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {struct hw_dma* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_PCI_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BNX2X_VF_CIDS ; 
 TYPE_5__* BP_VFDB (struct bnx2x*) ; 
 TYPE_4__* BP_VF_BULLETIN_DMA (struct bnx2x*) ; 
 TYPE_3__* BP_VF_MBX_DMA (struct bnx2x*) ; 
 int ILT_PAGE_CIDS ; 
 int /*<<< orphan*/  IS_SRIOV (struct bnx2x*) ; 

void bnx2x_iov_free_mem(struct bnx2x *bp)
{
	int i;

	if (!IS_SRIOV(bp))
		return;

	/* free vfs hw contexts */
	for (i = 0; i < BNX2X_VF_CIDS/ILT_PAGE_CIDS; i++) {
		struct hw_dma *cxt = &bp->vfdb->context[i];
		BNX2X_PCI_FREE(cxt->addr, cxt->mapping, cxt->size);
	}

	BNX2X_PCI_FREE(BP_VFDB(bp)->sp_dma.addr,
		       BP_VFDB(bp)->sp_dma.mapping,
		       BP_VFDB(bp)->sp_dma.size);

	BNX2X_PCI_FREE(BP_VF_MBX_DMA(bp)->addr,
		       BP_VF_MBX_DMA(bp)->mapping,
		       BP_VF_MBX_DMA(bp)->size);

	BNX2X_PCI_FREE(BP_VF_BULLETIN_DMA(bp)->addr,
		       BP_VF_BULLETIN_DMA(bp)->mapping,
		       BP_VF_BULLETIN_DMA(bp)->size);
}