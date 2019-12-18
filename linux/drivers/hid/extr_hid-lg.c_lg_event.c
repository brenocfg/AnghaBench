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
struct lg_drv_data {int quirks; } ;
struct hid_usage {scalar_t__ code; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int LG_FF4 ; 
 int LG_INVERT_HWHEEL ; 
 scalar_t__ REL_HWHEEL ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int lg4ff_adjust_input_event (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ,struct lg_drv_data*) ; 

__attribute__((used)) static int lg_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct lg_drv_data *drv_data = hid_get_drvdata(hdev);

	if ((drv_data->quirks & LG_INVERT_HWHEEL) && usage->code == REL_HWHEEL) {
		input_event(field->hidinput->input, usage->type, usage->code,
				-value);
		return 1;
	}
	if (drv_data->quirks & LG_FF4) {
		return lg4ff_adjust_input_event(hdev, field, usage, value, drv_data);
	}

	return 0;
}