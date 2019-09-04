#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_device {TYPE_1__** kobjs; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj_unregister; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_remove_s2idle_attr_group (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cpuidle_free_state_kobj(struct cpuidle_device *device, int i)
{
	cpuidle_remove_s2idle_attr_group(device->kobjs[i]);
	kobject_put(&device->kobjs[i]->kobj);
	wait_for_completion(&device->kobjs[i]->kobj_unregister);
	kfree(device->kobjs[i]);
	device->kobjs[i] = NULL;
}