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
struct sony_sc {int led_count; int* led_state; struct led_classdev** leds; } ;
struct led_classdev {TYPE_1__* dev; } ;
struct hid_device {int dummy; } ;
struct device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct sony_sc* hid_get_drvdata (struct hid_device*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static enum led_brightness sony_led_get_brightness(struct led_classdev *led)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = to_hid_device(dev);
	struct sony_sc *drv_data;

	int n;

	drv_data = hid_get_drvdata(hdev);
	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return LED_OFF;
	}

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n])
			return drv_data->led_state[n];
	}

	return LED_OFF;
}