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
struct vxlan_rdst {int dummy; } ;
struct vxlan_fdb {int dummy; } ;
struct vxlan_dev {int dummy; } ;
struct switchdev_notifier_vxlan_fdb_info {int dummy; } ;
struct notifier_block {int (* notifier_call ) (struct notifier_block*,int /*<<< orphan*/ ,struct switchdev_notifier_vxlan_fdb_info*) ;} ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE ; 
 int notifier_to_errno (int) ; 
 int stub1 (struct notifier_block*,int /*<<< orphan*/ ,struct switchdev_notifier_vxlan_fdb_info*) ; 
 int /*<<< orphan*/  vxlan_fdb_switchdev_notifier_info (struct vxlan_dev const*,struct vxlan_fdb const*,struct vxlan_rdst const*,struct netlink_ext_ack*,struct switchdev_notifier_vxlan_fdb_info*) ; 

__attribute__((used)) static int vxlan_fdb_notify_one(struct notifier_block *nb,
				const struct vxlan_dev *vxlan,
				const struct vxlan_fdb *f,
				const struct vxlan_rdst *rdst,
				struct netlink_ext_ack *extack)
{
	struct switchdev_notifier_vxlan_fdb_info fdb_info;
	int rc;

	vxlan_fdb_switchdev_notifier_info(vxlan, f, rdst, extack, &fdb_info);
	rc = nb->notifier_call(nb, SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE,
			       &fdb_info);
	return notifier_to_errno(rc);
}