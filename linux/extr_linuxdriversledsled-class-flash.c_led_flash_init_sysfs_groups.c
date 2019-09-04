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
struct led_flash_ops {scalar_t__ fault_get; scalar_t__ timeout_set; scalar_t__ flash_brightness_set; } ;
struct led_classdev {struct attribute_group const** groups; } ;
struct led_classdev_flash {struct attribute_group** sysfs_groups; struct led_flash_ops* ops; struct led_classdev led_cdev; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 struct attribute_group led_flash_brightness_group ; 
 struct attribute_group led_flash_fault_group ; 
 struct attribute_group led_flash_strobe_group ; 
 struct attribute_group led_flash_timeout_group ; 

__attribute__((used)) static void led_flash_init_sysfs_groups(struct led_classdev_flash *fled_cdev)
{
	struct led_classdev *led_cdev = &fled_cdev->led_cdev;
	const struct led_flash_ops *ops = fled_cdev->ops;
	const struct attribute_group **flash_groups = fled_cdev->sysfs_groups;

	int num_sysfs_groups = 0;

	flash_groups[num_sysfs_groups++] = &led_flash_strobe_group;

	if (ops->flash_brightness_set)
		flash_groups[num_sysfs_groups++] = &led_flash_brightness_group;

	if (ops->timeout_set)
		flash_groups[num_sysfs_groups++] = &led_flash_timeout_group;

	if (ops->fault_get)
		flash_groups[num_sysfs_groups++] = &led_flash_fault_group;

	led_cdev->groups = flash_groups;
}