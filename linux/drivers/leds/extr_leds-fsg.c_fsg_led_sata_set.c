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
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int FSG_LED_SATA_BIT ; 
 int* latch_address ; 
 int latch_value ; 

__attribute__((used)) static void fsg_led_sata_set(struct led_classdev *led_cdev,
			     enum led_brightness value)
{
	if (value) {
		latch_value &= ~(1 << FSG_LED_SATA_BIT);
		*latch_address = latch_value;
	} else {
		latch_value |=  (1 << FSG_LED_SATA_BIT);
		*latch_address = latch_value;
	}
}