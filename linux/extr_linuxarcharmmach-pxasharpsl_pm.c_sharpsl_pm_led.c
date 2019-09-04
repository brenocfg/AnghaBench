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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int SHARPSL_LED_ERROR ; 
 int SHARPSL_LED_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_charge_led_trigger ; 
 TYPE_1__ sharpsl_pm ; 

void sharpsl_pm_led(int val)
{
	if (val == SHARPSL_LED_ERROR) {
		dev_err(sharpsl_pm.dev, "Charging Error!\n");
	} else if (val == SHARPSL_LED_ON) {
		dev_dbg(sharpsl_pm.dev, "Charge LED On\n");
		led_trigger_event(sharpsl_charge_led_trigger, LED_FULL);
	} else {
		dev_dbg(sharpsl_pm.dev, "Charge LED Off\n");
		led_trigger_event(sharpsl_charge_led_trigger, LED_OFF);
	}
}