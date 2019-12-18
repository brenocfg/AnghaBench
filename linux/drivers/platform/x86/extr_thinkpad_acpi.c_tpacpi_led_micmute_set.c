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
 int /*<<< orphan*/  LED_AUDIO_MICMUTE ; 
 int LED_OFF ; 
 int tpacpi_led_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tpacpi_led_micmute_set(struct led_classdev *led_cdev,
				  enum led_brightness brightness)
{
	return tpacpi_led_set(LED_AUDIO_MICMUTE, brightness != LED_OFF);
}