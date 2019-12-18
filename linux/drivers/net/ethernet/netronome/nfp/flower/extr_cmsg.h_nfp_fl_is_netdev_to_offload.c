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
struct net_device {TYPE_1__* rtnl_link_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 scalar_t__ netif_is_geneve (struct net_device*) ; 
 scalar_t__ netif_is_gretap (struct net_device*) ; 
 scalar_t__ netif_is_vxlan (struct net_device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool nfp_fl_is_netdev_to_offload(struct net_device *netdev)
{
	if (!netdev->rtnl_link_ops)
		return false;
	if (!strcmp(netdev->rtnl_link_ops->kind, "openvswitch"))
		return true;
	if (netif_is_vxlan(netdev))
		return true;
	if (netif_is_geneve(netdev))
		return true;
	if (netif_is_gretap(netdev))
		return true;

	return false;
}