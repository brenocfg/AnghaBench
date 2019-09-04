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
struct subsys_interface {int dummy; } ;
struct device {int id; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UCODE_ERROR ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  mc_attr_group ; 
 scalar_t__ microcode_init_cpu (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mc_device_add(struct device *dev, struct subsys_interface *sif)
{
	int err, cpu = dev->id;

	if (!cpu_online(cpu))
		return 0;

	pr_debug("CPU%d added\n", cpu);

	err = sysfs_create_group(&dev->kobj, &mc_attr_group);
	if (err)
		return err;

	if (microcode_init_cpu(cpu, true) == UCODE_ERROR)
		return -EINVAL;

	return err;
}