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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  port_info; } ;

/* Variables and functions */
 int ice_get_link_status (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u64 ice_link_test(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	enum ice_status status;
	bool link_up = false;

	netdev_info(netdev, "link test\n");
	status = ice_get_link_status(np->vsi->port_info, &link_up);
	if (status) {
		netdev_err(netdev, "link query error, status = %d\n", status);
		return 1;
	}

	if (!link_up)
		return 2;

	return 0;
}