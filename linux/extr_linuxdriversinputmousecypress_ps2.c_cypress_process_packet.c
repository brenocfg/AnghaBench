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
struct psmouse {struct cytp_data* private; struct input_dev* dev; } ;
struct input_mt_pos {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct input_dev {int dummy; } ;
struct cytp_report_data {int contact_cnt; int /*<<< orphan*/  middle; int /*<<< orphan*/  right; int /*<<< orphan*/  left; struct cytp_contact* contacts; } ;
struct cytp_data {int dummy; } ;
struct cytp_contact {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int CYTP_MAX_MT_SLOTS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  cypress_parse_packet (struct psmouse*,struct cytp_data*,struct cytp_report_data*) ; 
 int /*<<< orphan*/  input_mt_assign_slots (struct input_dev*,int*,struct input_mt_pos*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_finger_count (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cypress_process_packet(struct psmouse *psmouse, bool zero_pkt)
{
	int i;
	struct input_dev *input = psmouse->dev;
	struct cytp_data *cytp = psmouse->private;
	struct cytp_report_data report_data;
	struct cytp_contact *contact;
	struct input_mt_pos pos[CYTP_MAX_MT_SLOTS];
	int slots[CYTP_MAX_MT_SLOTS];
	int n;

	cypress_parse_packet(psmouse, cytp, &report_data);

	n = report_data.contact_cnt;
	if (n > CYTP_MAX_MT_SLOTS)
		n = CYTP_MAX_MT_SLOTS;

	for (i = 0; i < n; i++) {
		contact = &report_data.contacts[i];
		pos[i].x = contact->x;
		pos[i].y = contact->y;
	}

	input_mt_assign_slots(input, slots, pos, n, 0);

	for (i = 0; i < n; i++) {
		contact = &report_data.contacts[i];
		input_mt_slot(input, slots[i]);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_abs(input, ABS_MT_POSITION_X, contact->x);
		input_report_abs(input, ABS_MT_POSITION_Y, contact->y);
		input_report_abs(input, ABS_MT_PRESSURE, contact->z);
	}

	input_mt_sync_frame(input);

	input_mt_report_finger_count(input, report_data.contact_cnt);

	input_report_key(input, BTN_LEFT, report_data.left);
	input_report_key(input, BTN_RIGHT, report_data.right);
	input_report_key(input, BTN_MIDDLE, report_data.middle);

	input_sync(input);
}