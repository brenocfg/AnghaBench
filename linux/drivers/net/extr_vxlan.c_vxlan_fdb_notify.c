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
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
#define  RTM_DELNEIGH 129 
#define  RTM_NEWNEIGH 128 
 int /*<<< orphan*/  __vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,struct vxlan_rdst*,int) ; 
 int vxlan_fdb_switchdev_call_notifiers (struct vxlan_dev*,struct vxlan_fdb*,struct vxlan_rdst*,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int vxlan_fdb_notify(struct vxlan_dev *vxlan, struct vxlan_fdb *fdb,
			    struct vxlan_rdst *rd, int type, bool swdev_notify,
			    struct netlink_ext_ack *extack)
{
	int err;

	if (swdev_notify) {
		switch (type) {
		case RTM_NEWNEIGH:
			err = vxlan_fdb_switchdev_call_notifiers(vxlan, fdb, rd,
								 true, extack);
			if (err)
				return err;
			break;
		case RTM_DELNEIGH:
			vxlan_fdb_switchdev_call_notifiers(vxlan, fdb, rd,
							   false, extack);
			break;
		}
	}

	__vxlan_fdb_notify(vxlan, fdb, rd, type);
	return 0;
}