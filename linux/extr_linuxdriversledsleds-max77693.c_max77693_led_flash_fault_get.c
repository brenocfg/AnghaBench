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
typedef  int /*<<< orphan*/  u32 ;
struct max77693_sub_led {int /*<<< orphan*/  flash_faults; } ;
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 struct max77693_sub_led* flcdev_to_sub_led (struct led_classdev_flash*) ; 

__attribute__((used)) static int max77693_led_flash_fault_get(
				struct led_classdev_flash *fled_cdev,
				u32 *fault)
{
	struct max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);

	*fault = sub_led->flash_faults;

	return 0;
}