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
struct TYPE_2__ {scalar_t__ inrange_state; int pad_input_event_flag; } ;
struct wacom_wac {TYPE_1__ hid_data; struct input_dev* pad_input; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct input_dev {int dummy; } ;
struct hid_report {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  PAD_DEVICE_ID ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void wacom_wac_pad_report(struct hid_device *hdev,
		struct hid_report *report, struct hid_field *field)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct input_dev *input = wacom_wac->pad_input;
	bool active = wacom_wac->hid_data.inrange_state != 0;

	/* report prox for expresskey events */
	if (wacom_wac->hid_data.pad_input_event_flag) {
		input_event(input, EV_ABS, ABS_MISC, active ? PAD_DEVICE_ID : 0);
		input_sync(input);
		if (!active)
			wacom_wac->hid_data.pad_input_event_flag = false;
	}
}