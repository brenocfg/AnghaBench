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
struct input_dev {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_5__ {int weak_magnitude; int strong_magnitude; } ;
struct TYPE_6__ {TYPE_1__ rumble; } ;
struct ff_effect {TYPE_2__ u; } ;
struct emsff_device {TYPE_4__* report; } ;
struct TYPE_8__ {TYPE_3__** field; } ;
struct TYPE_7__ {int* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  dbg_hid (char*,int,int) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int emsff_play(struct input_dev *dev, void *data,
			 struct ff_effect *effect)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct emsff_device *emsff = data;
	int weak, strong;

	weak = effect->u.rumble.weak_magnitude;
	strong = effect->u.rumble.strong_magnitude;

	dbg_hid("called with 0x%04x 0x%04x\n", strong, weak);

	weak = weak * 0xff / 0xffff;
	strong = strong * 0xff / 0xffff;

	emsff->report->field[0]->value[1] = weak;
	emsff->report->field[0]->value[2] = strong;

	dbg_hid("running with 0x%02x 0x%02x\n", strong, weak);
	hid_hw_request(hid, emsff->report, HID_REQ_SET_REPORT);

	return 0;
}