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
struct led_classdev {TYPE_1__* dev; } ;
struct hid_device {int dummy; } ;
struct device {int dummy; } ;
struct bigben_device {int led_state; struct led_classdev** leds; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int BIT (int) ; 
 int LED_OFF ; 
 int LED_ON ; 
 int NUM_LEDS ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct bigben_device* hid_get_drvdata (struct hid_device*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static enum led_brightness bigben_get_led(struct led_classdev *led)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hid = to_hid_device(dev);
	struct bigben_device *bigben = hid_get_drvdata(hid);
	int n;

	if (!bigben) {
		hid_err(hid, "no device data\n");
		return LED_OFF;
	}

	for (n = 0; n < NUM_LEDS; n++) {
		if (led == bigben->leds[n])
			return (bigben->led_state & BIT(n)) ? LED_ON : LED_OFF;
	}

	return LED_OFF;
}