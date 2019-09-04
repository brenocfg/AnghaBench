#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bnx2 {int num_req_rx_rings; int num_req_tx_rings; int irq_nvecs; int flags; int num_rx_rings; TYPE_3__* dev; void* num_tx_rings; TYPE_2__* pdev; TYPE_1__* irq_tbl; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_FLAG_MSIX_CAP ; 
 int BNX2_FLAG_MSI_CAP ; 
 int BNX2_FLAG_ONE_SHOT_MSI ; 
 int BNX2_FLAG_USING_MSI ; 
 int BNX2_FLAG_USING_MSIX ; 
 int RX_MAX_RINGS ; 
 int /*<<< orphan*/  bnx2_enable_msix (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_interrupt ; 
 int /*<<< orphan*/  bnx2_msi ; 
 int /*<<< orphan*/  bnx2_msi_1shot ; 
 int max (int,int) ; 
 void* min (int,int) ; 
 int netif_get_num_default_rss_queues () ; 
 int netif_set_real_num_rx_queues (TYPE_3__*,int) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (TYPE_3__*,void*) ; 
 scalar_t__ pci_enable_msi (TYPE_2__*) ; 
 void* rounddown_pow_of_two (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_setup_int_mode(struct bnx2 *bp, int dis_msi)
{
	int cpus = netif_get_num_default_rss_queues();
	int msix_vecs;

	if (!bp->num_req_rx_rings)
		msix_vecs = max(cpus + 1, bp->num_req_tx_rings);
	else if (!bp->num_req_tx_rings)
		msix_vecs = max(cpus, bp->num_req_rx_rings);
	else
		msix_vecs = max(bp->num_req_rx_rings, bp->num_req_tx_rings);

	msix_vecs = min(msix_vecs, RX_MAX_RINGS);

	bp->irq_tbl[0].handler = bnx2_interrupt;
	strcpy(bp->irq_tbl[0].name, bp->dev->name);
	bp->irq_nvecs = 1;
	bp->irq_tbl[0].vector = bp->pdev->irq;

	if ((bp->flags & BNX2_FLAG_MSIX_CAP) && !dis_msi)
		bnx2_enable_msix(bp, msix_vecs);

	if ((bp->flags & BNX2_FLAG_MSI_CAP) && !dis_msi &&
	    !(bp->flags & BNX2_FLAG_USING_MSIX)) {
		if (pci_enable_msi(bp->pdev) == 0) {
			bp->flags |= BNX2_FLAG_USING_MSI;
			if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
				bp->flags |= BNX2_FLAG_ONE_SHOT_MSI;
				bp->irq_tbl[0].handler = bnx2_msi_1shot;
			} else
				bp->irq_tbl[0].handler = bnx2_msi;

			bp->irq_tbl[0].vector = bp->pdev->irq;
		}
	}

	if (!bp->num_req_tx_rings)
		bp->num_tx_rings = rounddown_pow_of_two(bp->irq_nvecs);
	else
		bp->num_tx_rings = min(bp->irq_nvecs, bp->num_req_tx_rings);

	if (!bp->num_req_rx_rings)
		bp->num_rx_rings = bp->irq_nvecs;
	else
		bp->num_rx_rings = min(bp->irq_nvecs, bp->num_req_rx_rings);

	netif_set_real_num_tx_queues(bp->dev, bp->num_tx_rings);

	return netif_set_real_num_rx_queues(bp->dev, bp->num_rx_rings);
}