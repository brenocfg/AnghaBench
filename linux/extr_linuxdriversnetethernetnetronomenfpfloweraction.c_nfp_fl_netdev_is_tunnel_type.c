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
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int NFP_FL_TUNNEL_GENEVE ; 
 int NFP_FL_TUNNEL_VXLAN ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool nfp_fl_netdev_is_tunnel_type(struct net_device *out_dev,
					 enum nfp_flower_tun_type tun_type)
{
	if (!out_dev->rtnl_link_ops)
		return false;

	if (!strcmp(out_dev->rtnl_link_ops->kind, "vxlan"))
		return tun_type == NFP_FL_TUNNEL_VXLAN;

	if (!strcmp(out_dev->rtnl_link_ops->kind, "geneve"))
		return tun_type == NFP_FL_TUNNEL_GENEVE;

	return false;
}