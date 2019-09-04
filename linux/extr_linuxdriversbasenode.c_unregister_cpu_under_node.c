#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct device* get_cpu_device (unsigned int) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 TYPE_2__** node_devices ; 
 int /*<<< orphan*/  node_online (unsigned int) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int unregister_cpu_under_node(unsigned int cpu, unsigned int nid)
{
	struct device *obj;

	if (!node_online(nid))
		return 0;

	obj = get_cpu_device(cpu);
	if (!obj)
		return 0;

	sysfs_remove_link(&node_devices[nid]->dev.kobj,
			  kobject_name(&obj->kobj));
	sysfs_remove_link(&obj->kobj,
			  kobject_name(&node_devices[nid]->dev.kobj));

	return 0;
}