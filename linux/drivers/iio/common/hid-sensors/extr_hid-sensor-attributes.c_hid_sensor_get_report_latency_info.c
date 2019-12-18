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
typedef  int /*<<< orphan*/  u32 ;
struct hid_sensor_hub_device {int /*<<< orphan*/  hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  report_id; int /*<<< orphan*/  index; } ;
struct hid_sensor_common {TYPE_1__ report_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PROP_REPORT_LATENCY ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void hid_sensor_get_report_latency_info(struct hid_sensor_hub_device *hsdev,
					       u32 usage_id,
					       struct hid_sensor_common *st)
{
	sensor_hub_input_get_attribute_info(hsdev, HID_FEATURE_REPORT,
					    usage_id,
					    HID_USAGE_SENSOR_PROP_REPORT_LATENCY,
					    &st->report_latency);

	hid_dbg(hsdev->hdev, "Report latency attributes: %x:%x\n",
		st->report_latency.index, st->report_latency.report_id);
}