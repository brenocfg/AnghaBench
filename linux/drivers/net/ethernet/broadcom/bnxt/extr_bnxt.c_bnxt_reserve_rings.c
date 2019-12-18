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
struct bnxt {scalar_t__ total_irqs; int tx_nr_rings_per_tc; int tx_nr_rings; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNXT_NEW_RM (struct bnxt*) ; 
 int ENOMEM ; 
 int __bnxt_reserve_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_clear_int_mode (struct bnxt*) ; 
 scalar_t__ bnxt_get_num_msix (struct bnxt*) ; 
 int bnxt_init_int_mode (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_need_reserve_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_restart (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_stop (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int netdev_get_num_tc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_reset_tc (int /*<<< orphan*/ ) ; 

int bnxt_reserve_rings(struct bnxt *bp, bool irq_re_init)
{
	int tcs = netdev_get_num_tc(bp->dev);
	bool irq_cleared = false;
	int rc;

	if (!bnxt_need_reserve_rings(bp))
		return 0;

	if (irq_re_init && BNXT_NEW_RM(bp) &&
	    bnxt_get_num_msix(bp) != bp->total_irqs) {
		bnxt_ulp_irq_stop(bp);
		bnxt_clear_int_mode(bp);
		irq_cleared = true;
	}
	rc = __bnxt_reserve_rings(bp);
	if (irq_cleared) {
		if (!rc)
			rc = bnxt_init_int_mode(bp);
		bnxt_ulp_irq_restart(bp, rc);
	}
	if (rc) {
		netdev_err(bp->dev, "ring reservation/IRQ init failure rc: %d\n", rc);
		return rc;
	}
	if (tcs && (bp->tx_nr_rings_per_tc * tcs != bp->tx_nr_rings)) {
		netdev_err(bp->dev, "tx ring reservation failure\n");
		netdev_reset_tc(bp->dev);
		bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
		return -ENOMEM;
	}
	return 0;
}