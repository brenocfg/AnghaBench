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
struct picolcd_data {int led_state; struct led_classdev** led; } ;
struct led_classdev {TYPE_1__* dev; } ;
struct hid_device {int dummy; } ;
struct device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int LED_OFF ; 
 struct picolcd_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  picolcd_leds_set (struct picolcd_data*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static void picolcd_led_set_brightness(struct led_classdev *led_cdev,
			enum led_brightness value)
{
	struct device *dev;
	struct hid_device *hdev;
	struct picolcd_data *data;
	int i, state = 0;

	dev  = led_cdev->dev->parent;
	hdev = to_hid_device(dev);
	data = hid_get_drvdata(hdev);
	if (!data)
		return;
	for (i = 0; i < 8; i++) {
		if (led_cdev != data->led[i])
			continue;
		state = (data->led_state >> i) & 1;
		if (value == LED_OFF && state) {
			data->led_state &= ~(1 << i);
			picolcd_leds_set(data);
		} else if (value != LED_OFF && !state) {
			data->led_state |= 1 << i;
			picolcd_leds_set(data);
		}
		break;
	}
}