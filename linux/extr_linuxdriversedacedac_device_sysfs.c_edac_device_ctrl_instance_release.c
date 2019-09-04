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
struct kobject {int dummy; } ;
struct edac_device_instance {TYPE_1__* ctl; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct edac_device_instance* to_instance (struct kobject*) ; 

__attribute__((used)) static void edac_device_ctrl_instance_release(struct kobject *kobj)
{
	struct edac_device_instance *instance;

	edac_dbg(1, "\n");

	/* map from this kobj to the main control struct
	 * and then dec the main kobj count
	 */
	instance = to_instance(kobj);
	kobject_put(&instance->ctl->kobj);
}