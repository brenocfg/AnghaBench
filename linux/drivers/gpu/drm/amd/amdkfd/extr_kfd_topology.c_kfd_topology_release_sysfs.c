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
struct TYPE_2__ {int /*<<< orphan*/ * kobj_topology; int /*<<< orphan*/ * kobj_nodes; int /*<<< orphan*/  attr_props; int /*<<< orphan*/  attr_genid; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfd_remove_sysfs_node_tree () ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 TYPE_1__ sys_props ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kfd_topology_release_sysfs(void)
{
	kfd_remove_sysfs_node_tree();
	if (sys_props.kobj_topology) {
		sysfs_remove_file(sys_props.kobj_topology,
				&sys_props.attr_genid);
		sysfs_remove_file(sys_props.kobj_topology,
				&sys_props.attr_props);
		if (sys_props.kobj_nodes) {
			kobject_del(sys_props.kobj_nodes);
			kobject_put(sys_props.kobj_nodes);
			sys_props.kobj_nodes = NULL;
		}
		kobject_del(sys_props.kobj_topology);
		kobject_put(sys_props.kobj_topology);
		sys_props.kobj_topology = NULL;
	}
}