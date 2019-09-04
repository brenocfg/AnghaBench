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
struct led_flash_setting {unsigned int step; } ;
struct led_classdev_flash {struct led_flash_setting timeout; } ;
struct aat1290_led {struct led_classdev_flash fled_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAT1290_FLASH_SAFETY_TIMER_ADDR ; 
 unsigned int AAT1290_FLASH_TM_NUM_LEVELS ; 
 int /*<<< orphan*/  aat1290_as2cwire_write (struct aat1290_led*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aat1290_set_flash_safety_timer(struct aat1290_led *led,
					unsigned int micro_sec)
{
	struct led_classdev_flash *fled_cdev = &led->fled_cdev;
	struct led_flash_setting *flash_tm = &fled_cdev->timeout;
	int flash_tm_reg = AAT1290_FLASH_TM_NUM_LEVELS -
				(micro_sec / flash_tm->step) + 1;

	aat1290_as2cwire_write(led, AAT1290_FLASH_SAFETY_TIMER_ADDR,
							flash_tm_reg);
}