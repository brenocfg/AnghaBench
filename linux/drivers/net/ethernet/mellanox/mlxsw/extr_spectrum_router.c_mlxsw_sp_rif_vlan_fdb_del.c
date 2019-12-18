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
struct switchdev_notifier_fdb_info {char const* addr; int /*<<< orphan*/  info; int /*<<< orphan*/  vid; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_rif {struct net_device* dev; int /*<<< orphan*/  fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_FDB_DEL_TO_BRIDGE ; 
 struct net_device* br_fdb_find_port (struct net_device*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_switchdev_notifiers (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_8021q_vid (int /*<<< orphan*/ ) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static void mlxsw_sp_rif_vlan_fdb_del(struct mlxsw_sp_rif *rif, const char *mac)
{
	u16 vid = mlxsw_sp_fid_8021q_vid(rif->fid);
	struct switchdev_notifier_fdb_info info;
	struct net_device *br_dev;
	struct net_device *dev;

	br_dev = is_vlan_dev(rif->dev) ? vlan_dev_real_dev(rif->dev) : rif->dev;
	dev = br_fdb_find_port(br_dev, mac, vid);
	if (!dev)
		return;

	info.addr = mac;
	info.vid = vid;
	call_switchdev_notifiers(SWITCHDEV_FDB_DEL_TO_BRIDGE, dev, &info.info,
				 NULL);
}