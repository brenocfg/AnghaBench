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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bnxt {int flags; int /*<<< orphan*/  state; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int BNXT_FLAG_ALL_CONFIG_FEATS ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_GRO ; 
 int BNXT_FLAG_LRO ; 
 int BNXT_FLAG_NO_AGG_RINGS ; 
 int BNXT_FLAG_RFS ; 
 int BNXT_FLAG_STRIP_VLAN ; 
 int BNXT_FLAG_TPA ; 
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int NETIF_F_GRO_HW ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_LRO ; 
 int NETIF_F_NTUPLE ; 
 int /*<<< orphan*/  bnxt_close_nic (struct bnxt*,int,int) ; 
 int bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_set_ring_params (struct bnxt*) ; 
 int bnxt_set_tpa (struct bnxt*,int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_set_features(struct net_device *dev, netdev_features_t features)
{
	struct bnxt *bp = netdev_priv(dev);
	u32 flags = bp->flags;
	u32 changes;
	int rc = 0;
	bool re_init = false;
	bool update_tpa = false;

	flags &= ~BNXT_FLAG_ALL_CONFIG_FEATS;
	if (features & NETIF_F_GRO_HW)
		flags |= BNXT_FLAG_GRO;
	else if (features & NETIF_F_LRO)
		flags |= BNXT_FLAG_LRO;

	if (bp->flags & BNXT_FLAG_NO_AGG_RINGS)
		flags &= ~BNXT_FLAG_TPA;

	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		flags |= BNXT_FLAG_STRIP_VLAN;

	if (features & NETIF_F_NTUPLE)
		flags |= BNXT_FLAG_RFS;

	changes = flags ^ bp->flags;
	if (changes & BNXT_FLAG_TPA) {
		update_tpa = true;
		if ((bp->flags & BNXT_FLAG_TPA) == 0 ||
		    (flags & BNXT_FLAG_TPA) == 0 ||
		    (bp->flags & BNXT_FLAG_CHIP_P5))
			re_init = true;
	}

	if (changes & ~BNXT_FLAG_TPA)
		re_init = true;

	if (flags != bp->flags) {
		u32 old_flags = bp->flags;

		if (!test_bit(BNXT_STATE_OPEN, &bp->state)) {
			bp->flags = flags;
			if (update_tpa)
				bnxt_set_ring_params(bp);
			return rc;
		}

		if (re_init) {
			bnxt_close_nic(bp, false, false);
			bp->flags = flags;
			if (update_tpa)
				bnxt_set_ring_params(bp);

			return bnxt_open_nic(bp, false, false);
		}
		if (update_tpa) {
			bp->flags = flags;
			rc = bnxt_set_tpa(bp,
					  (flags & BNXT_FLAG_TPA) ?
					  true : false);
			if (rc)
				bp->flags = old_flags;
		}
	}
	return rc;
}