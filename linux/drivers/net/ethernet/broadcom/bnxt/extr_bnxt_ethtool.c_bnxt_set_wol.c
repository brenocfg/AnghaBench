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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct bnxt {int flags; int wol; } ;

/* Variables and functions */
 int BNXT_FLAG_WOL_CAP ; 
 int EBUSY ; 
 int EINVAL ; 
 int WAKE_MAGIC ; 
 scalar_t__ bnxt_hwrm_alloc_wol_fltr (struct bnxt*) ; 
 scalar_t__ bnxt_hwrm_free_wol_fltr (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct bnxt *bp = netdev_priv(dev);

	if (wol->wolopts & ~WAKE_MAGIC)
		return -EINVAL;

	if (wol->wolopts & WAKE_MAGIC) {
		if (!(bp->flags & BNXT_FLAG_WOL_CAP))
			return -EINVAL;
		if (!bp->wol) {
			if (bnxt_hwrm_alloc_wol_fltr(bp))
				return -EBUSY;
			bp->wol = 1;
		}
	} else {
		if (bp->wol) {
			if (bnxt_hwrm_free_wol_fltr(bp))
				return -EBUSY;
			bp->wol = 0;
		}
	}
	return 0;
}