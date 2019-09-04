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
typedef  void* u8 ;
struct sony_sc {int led_count; void** led_delay_on; void** led_delay_off; struct led_classdev** leds; } ;
struct led_classdev {TYPE_1__* dev; } ;
struct hid_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SONY_WORKER_STATE ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct sony_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  sony_schedule_work (struct sony_sc*,int /*<<< orphan*/ ) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static int sony_led_blink_set(struct led_classdev *led, unsigned long *delay_on,
				unsigned long *delay_off)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = to_hid_device(dev);
	struct sony_sc *drv_data = hid_get_drvdata(hdev);
	int n;
	u8 new_on, new_off;

	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return -EINVAL;
	}

	/* Max delay is 255 deciseconds or 2550 milliseconds */
	if (*delay_on > 2550)
		*delay_on = 2550;
	if (*delay_off > 2550)
		*delay_off = 2550;

	/* Blink at 1 Hz if both values are zero */
	if (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	new_on = *delay_on / 10;
	new_off = *delay_off / 10;

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n])
			break;
	}

	/* This LED is not registered on this device */
	if (n >= drv_data->led_count)
		return -EINVAL;

	/* Don't schedule work if the values didn't change */
	if (new_on != drv_data->led_delay_on[n] ||
		new_off != drv_data->led_delay_off[n]) {
		drv_data->led_delay_on[n] = new_on;
		drv_data->led_delay_off[n] = new_off;
		sony_schedule_work(drv_data, SONY_WORKER_STATE);
	}

	return 0;
}