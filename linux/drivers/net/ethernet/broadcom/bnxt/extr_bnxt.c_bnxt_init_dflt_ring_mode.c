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
struct bnxt {TYPE_1__* dev; int /*<<< orphan*/  flags; scalar_t__ tx_nr_rings; scalar_t__ tx_nr_rings_per_tc; } ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_RFS ; 
 int /*<<< orphan*/  NETIF_F_NTUPLE ; 
 int /*<<< orphan*/  bnxt_clear_int_mode (struct bnxt*) ; 
 int bnxt_init_int_mode (struct bnxt*) ; 
 scalar_t__ bnxt_rfs_capable (struct bnxt*) ; 
 scalar_t__ bnxt_rfs_supported (struct bnxt*) ; 
 int bnxt_set_dflt_rings (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_restart (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_stop (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*) ; 

__attribute__((used)) static int bnxt_init_dflt_ring_mode(struct bnxt *bp)
{
	int rc;

	if (bp->tx_nr_rings)
		return 0;

	bnxt_ulp_irq_stop(bp);
	bnxt_clear_int_mode(bp);
	rc = bnxt_set_dflt_rings(bp, true);
	if (rc) {
		netdev_err(bp->dev, "Not enough rings available.\n");
		goto init_dflt_ring_err;
	}
	rc = bnxt_init_int_mode(bp);
	if (rc)
		goto init_dflt_ring_err;

	bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
	if (bnxt_rfs_supported(bp) && bnxt_rfs_capable(bp)) {
		bp->flags |= BNXT_FLAG_RFS;
		bp->dev->features |= NETIF_F_NTUPLE;
	}
init_dflt_ring_err:
	bnxt_ulp_irq_restart(bp, rc);
	return rc;
}