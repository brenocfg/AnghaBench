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
struct hid_usage {int code; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int dummy; } ;
typedef  int __s32 ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
#define  ABS_RX 131 
#define  ABS_X 130 
#define  ABS_Y 129 
#define  ABS_Z 128 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int xinmo_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	switch (usage->code) {
	case ABS_X:
	case ABS_Y:
	case ABS_Z:
	case ABS_RX:
		if (value < -1) {
			input_event(field->hidinput->input, usage->type,
				usage->code, -1);
			return 1;
		}
		break;
	}

	return 0;
}