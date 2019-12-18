#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lg_drv_data {struct lg4ff_device_entry* device_props; } ;
struct TYPE_4__ {int product_id; int /*<<< orphan*/  range; } ;
struct lg4ff_device_entry {TYPE_2__ wdata; } ;
struct hid_usage {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
#define  ABS_X 129 
#define  USB_DEVICE_ID_LOGITECH_DFP_WHEEL 128 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lg4ff_adjust_dfp_x_axis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lg4ff_adjust_input_event(struct hid_device *hid, struct hid_field *field,
			     struct hid_usage *usage, s32 value, struct lg_drv_data *drv_data)
{
	struct lg4ff_device_entry *entry = drv_data->device_props;
	s32 new_value = 0;

	if (!entry) {
		hid_err(hid, "Device properties not found");
		return 0;
	}

	switch (entry->wdata.product_id) {
	case USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
		switch (usage->code) {
		case ABS_X:
			new_value = lg4ff_adjust_dfp_x_axis(value, entry->wdata.range);
			input_event(field->hidinput->input, usage->type, usage->code, new_value);
			return 1;
		default:
			return 0;
		}
	default:
		return 0;
	}
}