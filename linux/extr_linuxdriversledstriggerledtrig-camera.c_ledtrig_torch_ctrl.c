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
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_FULL ; 
 int LED_OFF ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ledtrig_torch ; 

void ledtrig_torch_ctrl(bool on)
{
	enum led_brightness brt = on ? LED_FULL : LED_OFF;

	led_trigger_event(ledtrig_torch, brt);
}