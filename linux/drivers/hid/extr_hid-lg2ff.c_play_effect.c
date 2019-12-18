#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lg2ff_device {TYPE_4__* report; } ;
struct input_dev {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_5__ {int strong_magnitude; int weak_magnitude; } ;
struct TYPE_6__ {TYPE_1__ rumble; } ;
struct ff_effect {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__** field; } ;
struct TYPE_7__ {int* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int play_effect(struct input_dev *dev, void *data,
			 struct ff_effect *effect)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct lg2ff_device *lg2ff = data;
	int weak, strong;

	strong = effect->u.rumble.strong_magnitude;
	weak = effect->u.rumble.weak_magnitude;

	if (weak || strong) {
		weak = weak * 0xff / 0xffff;
		strong = strong * 0xff / 0xffff;

		lg2ff->report->field[0]->value[0] = 0x51;
		lg2ff->report->field[0]->value[2] = weak;
		lg2ff->report->field[0]->value[4] = strong;
	} else {
		lg2ff->report->field[0]->value[0] = 0xf3;
		lg2ff->report->field[0]->value[2] = 0x00;
		lg2ff->report->field[0]->value[4] = 0x00;
	}

	hid_hw_request(hid, lg2ff->report, HID_REQ_SET_REPORT);
	return 0;
}