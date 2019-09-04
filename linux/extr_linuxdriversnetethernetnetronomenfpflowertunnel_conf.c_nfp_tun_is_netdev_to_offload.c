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
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool nfp_tun_is_netdev_to_offload(struct net_device *netdev)
{
	if (!netdev->rtnl_link_ops)
		return false;
	if (!strcmp(netdev->rtnl_link_ops->kind, "openvswitch"))
		return true;
	if (!strcmp(netdev->rtnl_link_ops->kind, "vxlan"))
		return true;

	return false;
}