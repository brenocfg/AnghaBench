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
struct vxlan_rdst {int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; } ;
struct vxlan_fdb {int dummy; } ;
struct vxlan_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELNEIGH ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_dst_free ; 
 int /*<<< orphan*/  vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,struct vxlan_rdst*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vxlan_fdb_dst_destroy(struct vxlan_dev *vxlan, struct vxlan_fdb *f,
				  struct vxlan_rdst *rd, bool swdev_notify)
{
	list_del_rcu(&rd->list);
	vxlan_fdb_notify(vxlan, f, rd, RTM_DELNEIGH, swdev_notify, NULL);
	call_rcu(&rd->rcu, vxlan_dst_free);
}