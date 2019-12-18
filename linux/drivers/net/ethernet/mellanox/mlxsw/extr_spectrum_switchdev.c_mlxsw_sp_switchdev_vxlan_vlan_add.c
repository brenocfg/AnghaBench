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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  vni; } ;
struct vxlan_dev {TYPE_1__ cfg; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ mlxsw_sp_bridge_8021q_vxlan_dev_find (int /*<<< orphan*/ ,scalar_t__) ; 
 int mlxsw_sp_bridge_8021q_vxlan_join (struct mlxsw_sp_bridge_device*,struct net_device const*,scalar_t__,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_vxlan_leave (struct mlxsw_sp*,struct net_device const*) ; 
 scalar_t__ mlxsw_sp_fid_8021q_vid (struct mlxsw_sp_fid*) ; 
 struct mlxsw_sp_fid* mlxsw_sp_fid_lookup_by_vni (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (struct mlxsw_sp_fid*) ; 
 struct vxlan_dev* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  netif_running (struct net_device const*) ; 

__attribute__((used)) static int
mlxsw_sp_switchdev_vxlan_vlan_add(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_bridge_device *bridge_device,
				  const struct net_device *vxlan_dev, u16 vid,
				  bool flag_untagged, bool flag_pvid,
				  struct netlink_ext_ack *extack)
{
	struct vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	__be32 vni = vxlan->cfg.vni;
	struct mlxsw_sp_fid *fid;
	u16 old_vid;
	int err;

	/* We cannot have the same VLAN as PVID and egress untagged on multiple
	 * VxLAN devices. Note that we get this notification before the VLAN is
	 * actually added to the bridge's database, so it is not possible for
	 * the lookup function to return 'vxlan_dev'
	 */
	if (flag_untagged && flag_pvid &&
	    mlxsw_sp_bridge_8021q_vxlan_dev_find(bridge_device->dev, vid)) {
		NL_SET_ERR_MSG_MOD(extack, "VLAN already mapped to a different VNI");
		return -EINVAL;
	}

	if (!netif_running(vxlan_dev))
		return 0;

	/* First case: FID is not associated with this VNI, but the new VLAN
	 * is both PVID and egress untagged. Need to enable NVE on the FID, if
	 * it exists
	 */
	fid = mlxsw_sp_fid_lookup_by_vni(mlxsw_sp, vni);
	if (!fid) {
		if (!flag_untagged || !flag_pvid)
			return 0;
		return mlxsw_sp_bridge_8021q_vxlan_join(bridge_device,
							vxlan_dev, vid, extack);
	}

	/* Second case: FID is associated with the VNI and the VLAN associated
	 * with the FID is the same as the notified VLAN. This means the flags
	 * (PVID / egress untagged) were toggled and that NVE should be
	 * disabled on the FID
	 */
	old_vid = mlxsw_sp_fid_8021q_vid(fid);
	if (vid == old_vid) {
		if (WARN_ON(flag_untagged && flag_pvid)) {
			mlxsw_sp_fid_put(fid);
			return -EINVAL;
		}
		mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, vxlan_dev);
		mlxsw_sp_fid_put(fid);
		return 0;
	}

	/* Third case: A new VLAN was configured on the VxLAN device, but this
	 * VLAN is not PVID, so there is nothing to do.
	 */
	if (!flag_pvid) {
		mlxsw_sp_fid_put(fid);
		return 0;
	}

	/* Fourth case: Thew new VLAN is PVID, which means the VLAN currently
	 * mapped to the VNI should be unmapped
	 */
	mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, vxlan_dev);
	mlxsw_sp_fid_put(fid);

	/* Fifth case: The new VLAN is also egress untagged, which means the
	 * VLAN needs to be mapped to the VNI
	 */
	if (!flag_untagged)
		return 0;

	err = mlxsw_sp_bridge_8021q_vxlan_join(bridge_device, vxlan_dev, vid,
					       extack);
	if (err)
		goto err_vxlan_join;

	return 0;

err_vxlan_join:
	mlxsw_sp_bridge_8021q_vxlan_join(bridge_device, vxlan_dev, old_vid,
					 NULL);
	return err;
}