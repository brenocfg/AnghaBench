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
struct net_device {char* name; } ;
struct msix_entry {int entry; scalar_t__ vector; } ;
struct bnx2 {int irq_nvecs; int flags; TYPE_1__* irq_tbl; int /*<<< orphan*/  pdev; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  name; scalar_t__ vector; } ;

/* Variables and functions */
 int BNX2_FLAG_ONE_SHOT_MSI ; 
 int BNX2_FLAG_USING_MSIX ; 
 scalar_t__ BNX2_MAX_MSIX_HW_VEC ; 
 int BNX2_MAX_MSIX_VEC ; 
 int /*<<< orphan*/  BNX2_MIN_MSIX_VEC ; 
 scalar_t__ BNX2_PCI_GRC_WINDOW2_BASE ; 
 scalar_t__ BNX2_PCI_GRC_WINDOW3_BASE ; 
 int /*<<< orphan*/  BNX2_PCI_MSIX_CONTROL ; 
 int /*<<< orphan*/  BNX2_PCI_MSIX_PBA_OFF_BIT ; 
 int /*<<< orphan*/  BNX2_PCI_MSIX_TBL_OFF_BIR ; 
 int /*<<< orphan*/  BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bnx2_msi_1shot ; 
 int /*<<< orphan*/  bnx2_setup_msix_tbl (struct bnx2*) ; 
 int pci_enable_msix_range (int /*<<< orphan*/ ,struct msix_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int const,char*,char*,int) ; 

__attribute__((used)) static void
bnx2_enable_msix(struct bnx2 *bp, int msix_vecs)
{
	int i, total_vecs;
	struct msix_entry msix_ent[BNX2_MAX_MSIX_VEC];
	struct net_device *dev = bp->dev;
	const int len = sizeof(bp->irq_tbl[0].name);

	bnx2_setup_msix_tbl(bp);
	BNX2_WR(bp, BNX2_PCI_MSIX_CONTROL, BNX2_MAX_MSIX_HW_VEC - 1);
	BNX2_WR(bp, BNX2_PCI_MSIX_TBL_OFF_BIR, BNX2_PCI_GRC_WINDOW2_BASE);
	BNX2_WR(bp, BNX2_PCI_MSIX_PBA_OFF_BIT, BNX2_PCI_GRC_WINDOW3_BASE);

	/*  Need to flush the previous three writes to ensure MSI-X
	 *  is setup properly */
	BNX2_RD(bp, BNX2_PCI_MSIX_CONTROL);

	for (i = 0; i < BNX2_MAX_MSIX_VEC; i++) {
		msix_ent[i].entry = i;
		msix_ent[i].vector = 0;
	}

	total_vecs = msix_vecs;
#ifdef BCM_CNIC
	total_vecs++;
#endif
	total_vecs = pci_enable_msix_range(bp->pdev, msix_ent,
					   BNX2_MIN_MSIX_VEC, total_vecs);
	if (total_vecs < 0)
		return;

	msix_vecs = total_vecs;
#ifdef BCM_CNIC
	msix_vecs--;
#endif
	bp->irq_nvecs = msix_vecs;
	bp->flags |= BNX2_FLAG_USING_MSIX | BNX2_FLAG_ONE_SHOT_MSI;
	for (i = 0; i < total_vecs; i++) {
		bp->irq_tbl[i].vector = msix_ent[i].vector;
		snprintf(bp->irq_tbl[i].name, len, "%s-%d", dev->name, i);
		bp->irq_tbl[i].handler = bnx2_msi_1shot;
	}
}