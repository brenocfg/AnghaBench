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
struct device {int /*<<< orphan*/  kobj; } ;
struct cpuidle_device_kobj {int /*<<< orphan*/  kobj; int /*<<< orphan*/  kobj_unregister; struct cpuidle_device* dev; } ;
struct cpuidle_device {struct cpuidle_device_kobj* kobj_dev; scalar_t__ cpu; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 struct device* get_cpu_device (unsigned long) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpuidle_device_kobj*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_cpuidle ; 
 struct cpuidle_device_kobj* kzalloc (int,int /*<<< orphan*/ ) ; 

int cpuidle_add_sysfs(struct cpuidle_device *dev)
{
	struct cpuidle_device_kobj *kdev;
	struct device *cpu_dev = get_cpu_device((unsigned long)dev->cpu);
	int error;

	/*
	 * Return if cpu_device is not setup for this CPU.
	 *
	 * This could happen if the arch did not set up cpu_device
	 * since this CPU is not in cpu_present mask and the
	 * driver did not send a correct CPU mask during registration.
	 * Without this check we would end up passing bogus
	 * value for &cpu_dev->kobj in kobject_init_and_add()
	 */
	if (!cpu_dev)
		return -ENODEV;

	kdev = kzalloc(sizeof(*kdev), GFP_KERNEL);
	if (!kdev)
		return -ENOMEM;
	kdev->dev = dev;
	dev->kobj_dev = kdev;

	init_completion(&kdev->kobj_unregister);

	error = kobject_init_and_add(&kdev->kobj, &ktype_cpuidle, &cpu_dev->kobj,
				   "cpuidle");
	if (error) {
		kfree(kdev);
		return error;
	}

	kobject_uevent(&kdev->kobj, KOBJ_ADD);

	return 0;
}