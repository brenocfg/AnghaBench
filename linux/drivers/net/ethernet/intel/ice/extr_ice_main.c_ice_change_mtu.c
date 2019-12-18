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
typedef  int u8 ;
struct net_device {int mtu; int min_mtu; int max_mtu; } ;
struct ice_vsi {int /*<<< orphan*/  state; struct ice_pf* back; } ;
struct ice_pf {int /*<<< orphan*/  state; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int ice_down (struct ice_vsi*) ; 
 scalar_t__ ice_is_reset_in_progress (int /*<<< orphan*/ ) ; 
 int ice_up (struct ice_vsi*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ice_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	u8 count = 0;

	if (new_mtu == netdev->mtu) {
		netdev_warn(netdev, "MTU is already %u\n", netdev->mtu);
		return 0;
	}

	if (new_mtu < netdev->min_mtu) {
		netdev_err(netdev, "new MTU invalid. min_mtu is %d\n",
			   netdev->min_mtu);
		return -EINVAL;
	} else if (new_mtu > netdev->max_mtu) {
		netdev_err(netdev, "new MTU invalid. max_mtu is %d\n",
			   netdev->min_mtu);
		return -EINVAL;
	}
	/* if a reset is in progress, wait for some time for it to complete */
	do {
		if (ice_is_reset_in_progress(pf->state)) {
			count++;
			usleep_range(1000, 2000);
		} else {
			break;
		}

	} while (count < 100);

	if (count == 100) {
		netdev_err(netdev, "can't change MTU. Device is busy\n");
		return -EBUSY;
	}

	netdev->mtu = new_mtu;

	/* if VSI is up, bring it down and then back up */
	if (!test_and_set_bit(__ICE_DOWN, vsi->state)) {
		int err;

		err = ice_down(vsi);
		if (err) {
			netdev_err(netdev, "change MTU if_up err %d\n", err);
			return err;
		}

		err = ice_up(vsi);
		if (err) {
			netdev_err(netdev, "change MTU if_up err %d\n", err);
			return err;
		}
	}

	netdev_info(netdev, "changed MTU to %d\n", new_mtu);
	return 0;
}