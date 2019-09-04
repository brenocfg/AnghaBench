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
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_1__* vsw; int /*<<< orphan*/  vsi_num; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  sw_id; } ;

/* Variables and functions */
 int ice_vsi_open (struct ice_vsi*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

__attribute__((used)) static int ice_open(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	int err;

	netif_carrier_off(netdev);

	err = ice_vsi_open(vsi);

	if (err)
		netdev_err(netdev, "Failed to open VSI 0x%04X on switch 0x%04X\n",
			   vsi->vsi_num, vsi->vsw->sw_id);
	return err;
}