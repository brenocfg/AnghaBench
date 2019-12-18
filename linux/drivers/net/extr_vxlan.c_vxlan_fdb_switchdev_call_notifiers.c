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
struct vxlan_dev {int /*<<< orphan*/  dev; } ;
struct switchdev_notifier_vxlan_fdb_info {int /*<<< orphan*/  info; } ;
struct netlink_ext_ack {int dummy; } ;
typedef  enum switchdev_notifier_type { ____Placeholder_switchdev_notifier_type } switchdev_notifier_type ;

/* Variables and functions */
 int SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE ; 
 int SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 
 int call_switchdev_notifiers (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int notifier_to_errno (int) ; 
 int /*<<< orphan*/  vxlan_fdb_switchdev_notifier_info (struct vxlan_dev*,struct vxlan_fdb*,struct vxlan_rdst*,int /*<<< orphan*/ *,struct switchdev_notifier_vxlan_fdb_info*) ; 

__attribute__((used)) static int vxlan_fdb_switchdev_call_notifiers(struct vxlan_dev *vxlan,
					      struct vxlan_fdb *fdb,
					      struct vxlan_rdst *rd,
					      bool adding,
					      struct netlink_ext_ack *extack)
{
	struct switchdev_notifier_vxlan_fdb_info info;
	enum switchdev_notifier_type notifier_type;
	int ret;

	if (WARN_ON(!rd))
		return 0;

	notifier_type = adding ? SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE
			       : SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE;
	vxlan_fdb_switchdev_notifier_info(vxlan, fdb, rd, NULL, &info);
	ret = call_switchdev_notifiers(notifier_type, vxlan->dev,
				       &info.info, extack);
	return notifier_to_errno(ret);
}