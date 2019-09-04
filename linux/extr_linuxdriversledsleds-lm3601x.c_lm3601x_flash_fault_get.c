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
struct lm3601x_led {int /*<<< orphan*/  last_flag; } ;
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 struct lm3601x_led* fled_cdev_to_led (struct led_classdev_flash*) ; 
 int /*<<< orphan*/  lm3601x_read_faults (struct lm3601x_led*) ; 

__attribute__((used)) static int lm3601x_flash_fault_get(struct led_classdev_flash *fled_cdev,
				u32 *fault)
{
	struct lm3601x_led *led = fled_cdev_to_led(fled_cdev);

	lm3601x_read_faults(led);

	*fault = led->last_flag;

	return 0;
}