#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_3__* back; struct ice_port_info* port_info; } ;
struct ice_port_info {TYPE_2__* hw; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  sq_last_status; } ;
struct TYPE_5__ {TYPE_1__ adminq; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int ice_aq_set_link_restart_an (struct ice_port_info*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_nway_reset(struct net_device *netdev)
{
	/* restart autonegotiation */
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_port_info *pi;
	enum ice_status status;

	pi = vsi->port_info;
	/* If VSI state is up, then restart autoneg with link up */
	if (!test_bit(__ICE_DOWN, vsi->back->state))
		status = ice_aq_set_link_restart_an(pi, true, NULL);
	else
		status = ice_aq_set_link_restart_an(pi, false, NULL);

	if (status) {
		netdev_info(netdev, "link restart failed, err %d aq_err %d\n",
			    status, pi->hw->adminq.sq_last_status);
		return -EIO;
	}

	return 0;
}