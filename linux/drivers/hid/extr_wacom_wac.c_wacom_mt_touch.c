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
struct TYPE_3__ {scalar_t__ type; } ;
struct wacom_wac {unsigned char* data; int num_contacts_left; TYPE_2__* shared; TYPE_1__ features; struct input_dev* touch_input; } ;
struct input_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  touch_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 scalar_t__ MTTPC ; 
 scalar_t__ MTTPC_B ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int WACOM_BYTES_PER_MT_PACKET ; 
 int get_unaligned_le16 (unsigned char*) ; 
 int input_mt_get_slot_by_key (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 scalar_t__ report_touch_events (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_wac_finger_count_touches (struct wacom_wac*) ; 

__attribute__((used)) static int wacom_mt_touch(struct wacom_wac *wacom)
{
	struct input_dev *input = wacom->touch_input;
	unsigned char *data = wacom->data;
	int i;
	int current_num_contacts = data[2];
	int contacts_to_send = 0;
	int x_offset = 0;

	/* MTTPC does not support Height and Width */
	if (wacom->features.type == MTTPC || wacom->features.type == MTTPC_B)
		x_offset = -4;

	/*
	 * First packet resets the counter since only the first
	 * packet in series will have non-zero current_num_contacts.
	 */
	if (current_num_contacts)
		wacom->num_contacts_left = current_num_contacts;

	/* There are at most 5 contacts per packet */
	contacts_to_send = min(5, wacom->num_contacts_left);

	for (i = 0; i < contacts_to_send; i++) {
		int offset = (WACOM_BYTES_PER_MT_PACKET + x_offset) * i + 3;
		bool touch = (data[offset] & 0x1) && report_touch_events(wacom);
		int id = get_unaligned_le16(&data[offset + 1]);
		int slot = input_mt_get_slot_by_key(input, id);

		if (slot < 0)
			continue;

		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		if (touch) {
			int x = get_unaligned_le16(&data[offset + x_offset + 7]);
			int y = get_unaligned_le16(&data[offset + x_offset + 9]);
			input_report_abs(input, ABS_MT_POSITION_X, x);
			input_report_abs(input, ABS_MT_POSITION_Y, y);
		}
	}
	input_mt_sync_frame(input);

	wacom->num_contacts_left -= contacts_to_send;
	if (wacom->num_contacts_left <= 0) {
		wacom->num_contacts_left = 0;
		wacom->shared->touch_down = wacom_wac_finger_count_touches(wacom);
	}
	return 1;
}