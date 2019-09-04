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
struct bnxt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool bnxt_rfs_capable(struct bnxt *bp)
{
#ifdef CONFIG_RFS_ACCEL
	int vnics, max_vnics, max_rss_ctxs;

	if (!(bp->flags & BNXT_FLAG_MSIX_CAP) || !bnxt_can_reserve_rings(bp))
		return false;

	vnics = 1 + bp->rx_nr_rings;
	max_vnics = bnxt_get_max_func_vnics(bp);
	max_rss_ctxs = bnxt_get_max_func_rss_ctxs(bp);

	/* RSS contexts not a limiting factor */
	if (bp->flags & BNXT_FLAG_NEW_RSS_CAP)
		max_rss_ctxs = max_vnics;
	if (vnics > max_vnics || vnics > max_rss_ctxs) {
		if (bp->rx_nr_rings > 1)
			netdev_warn(bp->dev,
				    "Not enough resources to support NTUPLE filters, enough resources for up to %d rx rings\n",
				    min(max_rss_ctxs - 1, max_vnics - 1));
		return false;
	}

	if (!BNXT_NEW_RM(bp))
		return true;

	if (vnics == bp->hw_resc.resv_vnics)
		return true;

	bnxt_hwrm_reserve_rings(bp, 0, 0, 0, 0, vnics);
	if (vnics <= bp->hw_resc.resv_vnics)
		return true;

	netdev_warn(bp->dev, "Unable to reserve resources to support NTUPLE filters.\n");
	bnxt_hwrm_reserve_rings(bp, 0, 0, 0, 0, 1);
	return false;
#else
	return false;
#endif
}