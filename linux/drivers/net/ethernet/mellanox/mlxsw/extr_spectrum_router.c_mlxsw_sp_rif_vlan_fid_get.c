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
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  mlxsw_sp; struct net_device* dev; } ;
struct mlxsw_sp_fid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlxsw_sp_fid* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 int br_vlan_get_pvid (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 struct mlxsw_sp_fid* mlxsw_sp_bridge_fid_get (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  netif_is_bridge_master (struct net_device*) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 

__attribute__((used)) static struct mlxsw_sp_fid *
mlxsw_sp_rif_vlan_fid_get(struct mlxsw_sp_rif *rif,
			  struct netlink_ext_ack *extack)
{
	struct net_device *br_dev = rif->dev;
	u16 vid;
	int err;

	if (is_vlan_dev(rif->dev)) {
		vid = vlan_dev_vlan_id(rif->dev);
		br_dev = vlan_dev_real_dev(rif->dev);
		if (WARN_ON(!netif_is_bridge_master(br_dev)))
			return ERR_PTR(-EINVAL);
	} else {
		err = br_vlan_get_pvid(rif->dev, &vid);
		if (err < 0 || !vid) {
			NL_SET_ERR_MSG_MOD(extack, "Couldn't determine bridge PVID");
			return ERR_PTR(-EINVAL);
		}
	}

	return mlxsw_sp_bridge_fid_get(rif->mlxsw_sp, br_dev, vid, extack);
}