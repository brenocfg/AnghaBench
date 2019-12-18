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
struct icade_key {int /*<<< orphan*/  press; int /*<<< orphan*/  to; } ;
struct hid_usage {int hid; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int HID_CLAIMED_INPUT ; 
 int HID_USAGE ; 
 struct icade_key* icade_find_translation (int) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icade_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	const struct icade_key *trans;

	if (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		return 0;

	/* We ignore the fake key up, and act only on key down */
	if (!value)
		return 1;

	trans = icade_find_translation(usage->hid & HID_USAGE);

	if (!trans)
		return 1;

	input_event(field->hidinput->input, usage->type,
			trans->to, trans->press);

	return 1;
}