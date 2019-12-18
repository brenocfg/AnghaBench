#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct input_dev {struct input_absinfo* absinfo; } ;
struct input_absinfo {int maximum; int minimum; } ;
struct hid_usage {size_t code; } ;

/* Variables and functions */

__attribute__((used)) static int wacom_offset_rotation(struct input_dev *input, struct hid_usage *usage,
				 int value, int num, int denom)
{
	struct input_absinfo *abs = &input->absinfo[usage->code];
	int range = (abs->maximum - abs->minimum + 1);

	value += num*range/denom;
	if (value > abs->maximum)
		value -= range;
	else if (value < abs->minimum)
		value += range;
	return value;
}