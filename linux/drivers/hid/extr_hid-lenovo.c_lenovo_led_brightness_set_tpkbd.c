#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct led_classdev {TYPE_1__* dev; } ;
struct lenovo_drvdata_tpkbd {int led_state; struct led_classdev led_micmute; } ;
struct hid_report {TYPE_3__** field; } ;
struct hid_device {TYPE_2__* report_enum; } ;
struct device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_6__ {int* value; } ;
struct TYPE_5__ {struct hid_report** report_id_hash; } ;
struct TYPE_4__ {struct device* parent; } ;

/* Variables and functions */
 size_t HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int LED_OFF ; 
 struct lenovo_drvdata_tpkbd* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static void lenovo_led_brightness_set_tpkbd(struct led_classdev *led_cdev,
			enum led_brightness value)
{
	struct device *dev = led_cdev->dev->parent;
	struct hid_device *hdev = to_hid_device(dev);
	struct lenovo_drvdata_tpkbd *data_pointer = hid_get_drvdata(hdev);
	struct hid_report *report;
	int led_nr = 0;

	if (led_cdev == &data_pointer->led_micmute)
		led_nr = 1;

	if (value == LED_OFF)
		data_pointer->led_state &= ~(1 << led_nr);
	else
		data_pointer->led_state |= 1 << led_nr;

	report = hdev->report_enum[HID_OUTPUT_REPORT].report_id_hash[3];
	report->field[0]->value[0] = (data_pointer->led_state >> 0) & 1;
	report->field[0]->value[1] = (data_pointer->led_state >> 1) & 1;
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
}