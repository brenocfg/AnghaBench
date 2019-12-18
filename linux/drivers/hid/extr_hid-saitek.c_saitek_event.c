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
struct saitek_sc {int quirks; } ;
struct input_dev {int dummy; } ;
struct hid_usage {scalar_t__ type; int code; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int dummy; } ;
typedef  scalar_t__ __s32 ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int BTN_MOUSE ; 
 scalar_t__ EV_KEY ; 
 int SAITEK_RELEASE_MODE_MMO7 ; 
 int SAITEK_RELEASE_MODE_RAT7 ; 
 struct saitek_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 

__attribute__((used)) static int saitek_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct saitek_sc *ssc = hid_get_drvdata(hdev);
	struct input_dev *input = field->hidinput->input;

	if (usage->type == EV_KEY && value &&
			(((ssc->quirks & SAITEK_RELEASE_MODE_RAT7) &&
			  usage->code - BTN_MOUSE == 10) ||
			((ssc->quirks & SAITEK_RELEASE_MODE_MMO7) &&
			 usage->code - BTN_MOUSE == 15))) {

		input_report_key(input, usage->code, 1);

		/* report missing release event */
		input_report_key(input, usage->code, 0);

		return 1;
	}

	return 0;
}