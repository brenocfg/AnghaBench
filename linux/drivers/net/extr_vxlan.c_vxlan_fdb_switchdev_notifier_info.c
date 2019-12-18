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
struct vxlan_rdst {int /*<<< orphan*/  offloaded; int /*<<< orphan*/  remote_ifindex; int /*<<< orphan*/  remote_vni; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; } ;
struct vxlan_fdb {int flags; int /*<<< orphan*/  vni; int /*<<< orphan*/  eth_addr; } ;
struct vxlan_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct netlink_ext_ack* extack; int /*<<< orphan*/  dev; } ;
struct switchdev_notifier_vxlan_fdb_info {int added_by_user; int /*<<< orphan*/  offloaded; int /*<<< orphan*/  vni; int /*<<< orphan*/  eth_addr; int /*<<< orphan*/  remote_ifindex; int /*<<< orphan*/  remote_vni; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; TYPE_1__ info; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int NTF_VXLAN_ADDED_BY_USER ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxlan_fdb_switchdev_notifier_info(const struct vxlan_dev *vxlan,
			    const struct vxlan_fdb *fdb,
			    const struct vxlan_rdst *rd,
			    struct netlink_ext_ack *extack,
			    struct switchdev_notifier_vxlan_fdb_info *fdb_info)
{
	fdb_info->info.dev = vxlan->dev;
	fdb_info->info.extack = extack;
	fdb_info->remote_ip = rd->remote_ip;
	fdb_info->remote_port = rd->remote_port;
	fdb_info->remote_vni = rd->remote_vni;
	fdb_info->remote_ifindex = rd->remote_ifindex;
	memcpy(fdb_info->eth_addr, fdb->eth_addr, ETH_ALEN);
	fdb_info->vni = fdb->vni;
	fdb_info->offloaded = rd->offloaded;
	fdb_info->added_by_user = fdb->flags & NTF_VXLAN_ADDED_BY_USER;
}