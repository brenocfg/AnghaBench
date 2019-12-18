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
struct TYPE_2__ {int resv_vnics; } ;
struct bnxt {int flags; int rx_nr_rings; int /*<<< orphan*/  dev; TYPE_1__ hw_resc; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_MSIX_CAP ; 
 int BNXT_FLAG_NEW_RSS_CAP ; 
 int /*<<< orphan*/  BNXT_NEW_RM (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_can_reserve_rings (struct bnxt*) ; 
 int bnxt_get_max_func_rss_ctxs (struct bnxt*) ; 
 int bnxt_get_max_func_vnics (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_reserve_rings (struct bnxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bnxt_rfs_supported (struct bnxt*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool bnxt_rfs_capable(struct bnxt *bp)
{
#ifdef CONFIG_RFS_ACCEL
	int vnics, max_vnics, max_rss_ctxs;

	if (bp->flags & BNXT_FLAG_CHIP_P5)
		return bnxt_rfs_supported(bp);
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

	bnxt_hwrm_reserve_rings(bp, 0, 0, 0, 0, 0, vnics);
	if (vnics <= bp->hw_resc.resv_vnics)
		return true;

	netdev_warn(bp->dev, "Unable to reserve resources to support NTUPLE filters.\n");
	bnxt_hwrm_reserve_rings(bp, 0, 0, 0, 0, 0, 1);
	return false;
#else
	return false;
#endif
}