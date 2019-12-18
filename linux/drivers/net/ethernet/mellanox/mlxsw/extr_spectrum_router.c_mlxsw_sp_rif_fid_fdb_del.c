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
struct switchdev_notifier_fdb_info {char const* addr; int /*<<< orphan*/  info; scalar_t__ vid; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_FDB_DEL_TO_BRIDGE ; 
 struct net_device* br_fdb_find_port (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_switchdev_notifiers (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_rif_fid_fdb_del(struct mlxsw_sp_rif *rif, const char *mac)
{
	struct switchdev_notifier_fdb_info info;
	struct net_device *dev;

	dev = br_fdb_find_port(rif->dev, mac, 0);
	if (!dev)
		return;

	info.addr = mac;
	info.vid = 0;
	call_switchdev_notifiers(SWITCHDEV_FDB_DEL_TO_BRIDGE, dev, &info.info,
				 NULL);
}