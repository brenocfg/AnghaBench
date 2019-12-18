#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {char* name; void* mode; } ;
struct TYPE_6__ {TYPE_1__ attr_props; scalar_t__ kobj_topology; TYPE_1__ attr_genid; int /*<<< orphan*/  kobj_nodes; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* KFD_SYSFS_FILE_MODE ; 
 scalar_t__ kfd_alloc_struct (scalar_t__) ; 
 int kfd_build_sysfs_node_tree () ; 
 TYPE_4__* kfd_device ; 
 int /*<<< orphan*/  kfd_remove_sysfs_node_tree () ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,scalar_t__) ; 
 int kobject_init_and_add (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 TYPE_3__ sys_props ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_1__*) ; 
 int sysfs_create_file (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  sysprops_type ; 

__attribute__((used)) static int kfd_topology_update_sysfs(void)
{
	int ret;

	pr_info("Creating topology SYSFS entries\n");
	if (!sys_props.kobj_topology) {
		sys_props.kobj_topology =
				kfd_alloc_struct(sys_props.kobj_topology);
		if (!sys_props.kobj_topology)
			return -ENOMEM;

		ret = kobject_init_and_add(sys_props.kobj_topology,
				&sysprops_type,  &kfd_device->kobj,
				"topology");
		if (ret < 0)
			return ret;

		sys_props.kobj_nodes = kobject_create_and_add("nodes",
				sys_props.kobj_topology);
		if (!sys_props.kobj_nodes)
			return -ENOMEM;

		sys_props.attr_genid.name = "generation_id";
		sys_props.attr_genid.mode = KFD_SYSFS_FILE_MODE;
		sysfs_attr_init(&sys_props.attr_genid);
		ret = sysfs_create_file(sys_props.kobj_topology,
				&sys_props.attr_genid);
		if (ret < 0)
			return ret;

		sys_props.attr_props.name = "system_properties";
		sys_props.attr_props.mode = KFD_SYSFS_FILE_MODE;
		sysfs_attr_init(&sys_props.attr_props);
		ret = sysfs_create_file(sys_props.kobj_topology,
				&sys_props.attr_props);
		if (ret < 0)
			return ret;
	}

	kfd_remove_sysfs_node_tree();

	return kfd_build_sysfs_node_tree();
}