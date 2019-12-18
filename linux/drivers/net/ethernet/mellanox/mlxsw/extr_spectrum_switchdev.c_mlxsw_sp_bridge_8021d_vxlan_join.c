#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  vni; } ;
struct vxlan_dev {TYPE_1__ cfg; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_nve_params {struct net_device const* dev; int /*<<< orphan*/  vni; int /*<<< orphan*/  type; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {TYPE_2__* dev; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_SP_NVE_TYPE_VXLAN ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct mlxsw_sp_fid* mlxsw_sp_fid_8021d_lookup (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (struct mlxsw_sp_fid*) ; 
 scalar_t__ mlxsw_sp_fid_vni_is_set (struct mlxsw_sp_fid*) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (TYPE_2__*) ; 
 int mlxsw_sp_nve_fid_enable (struct mlxsw_sp*,struct mlxsw_sp_fid*,struct mlxsw_sp_nve_params*,struct netlink_ext_ack*) ; 
 struct vxlan_dev* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int
mlxsw_sp_bridge_8021d_vxlan_join(struct mlxsw_sp_bridge_device *bridge_device,
				 const struct net_device *vxlan_dev, u16 vid,
				 struct netlink_ext_ack *extack)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);
	struct vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	struct mlxsw_sp_nve_params params = {
		.type = MLXSW_SP_NVE_TYPE_VXLAN,
		.vni = vxlan->cfg.vni,
		.dev = vxlan_dev,
	};
	struct mlxsw_sp_fid *fid;
	int err;

	fid = mlxsw_sp_fid_8021d_lookup(mlxsw_sp, bridge_device->dev->ifindex);
	if (!fid) {
		NL_SET_ERR_MSG_MOD(extack, "Did not find a corresponding FID");
		return -EINVAL;
	}

	if (mlxsw_sp_fid_vni_is_set(fid)) {
		NL_SET_ERR_MSG_MOD(extack, "VNI is already set on FID");
		err = -EINVAL;
		goto err_vni_exists;
	}

	err = mlxsw_sp_nve_fid_enable(mlxsw_sp, fid, &params, extack);
	if (err)
		goto err_nve_fid_enable;

	/* The tunnel port does not hold a reference on the FID. Only
	 * local ports and the router port
	 */
	mlxsw_sp_fid_put(fid);

	return 0;

err_nve_fid_enable:
err_vni_exists:
	mlxsw_sp_fid_put(fid);
	return err;
}