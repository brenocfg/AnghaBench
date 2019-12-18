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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hid_time_state {TYPE_1__* info; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct TYPE_2__ {int report_id; int size; scalar_t__ attrib_id; scalar_t__ units; scalar_t__ unit_expo; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 scalar_t__ HID_USAGE_SENSOR_TIME_SECOND ; 
 scalar_t__ HID_USAGE_SENSOR_UNITS_NOT_SPECIFIED ; 
 scalar_t__ HID_USAGE_SENSOR_UNITS_SECOND ; 
 int TIME_RTC_CHANNEL_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * hid_time_addresses ; 
 int /*<<< orphan*/  hid_time_attrib_name (scalar_t__) ; 
 scalar_t__ sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int hid_time_parse_report(struct platform_device *pdev,
				struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				struct hid_time_state *time_state)
{
	int report_id, i;

	for (i = 0; i < TIME_RTC_CHANNEL_MAX; ++i)
		if (sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT, usage_id,
				hid_time_addresses[i],
				&time_state->info[i]) < 0)
			return -EINVAL;
	/* Check the (needed) attributes for sanity */
	report_id = time_state->info[0].report_id;
	if (report_id < 0) {
		dev_err(&pdev->dev, "bad report ID!\n");
		return -EINVAL;
	}
	for (i = 0; i < TIME_RTC_CHANNEL_MAX; ++i) {
		if (time_state->info[i].report_id != report_id) {
			dev_err(&pdev->dev,
				"not all needed attributes inside the same report!\n");
			return -EINVAL;
		}
		if (time_state->info[i].size == 3 ||
				time_state->info[i].size > 4) {
			dev_err(&pdev->dev,
				"attribute '%s' not 8, 16 or 32 bits wide!\n",
				hid_time_attrib_name(
					time_state->info[i].attrib_id));
			return -EINVAL;
		}
		if (time_state->info[i].units !=
				HID_USAGE_SENSOR_UNITS_NOT_SPECIFIED &&
				/* allow attribute seconds with unit seconds */
				!(time_state->info[i].attrib_id ==
				HID_USAGE_SENSOR_TIME_SECOND &&
				time_state->info[i].units ==
				HID_USAGE_SENSOR_UNITS_SECOND)) {
			dev_err(&pdev->dev,
				"attribute '%s' hasn't a unit of type 'none'!\n",
				hid_time_attrib_name(
					time_state->info[i].attrib_id));
			return -EINVAL;
		}
		if (time_state->info[i].unit_expo) {
			dev_err(&pdev->dev,
				"attribute '%s' hasn't a unit exponent of 1!\n",
				hid_time_attrib_name(
					time_state->info[i].attrib_id));
			return -EINVAL;
		}
	}

	return 0;
}