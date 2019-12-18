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
typedef  int u8 ;
struct alps_dev {int max_fingers; int /*<<< orphan*/  input2; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
#define  U1_ABSOLUTE_REPORT_ID 131 
#define  U1_FEATURE_REPORT_ID 130 
#define  U1_MOUSE_REPORT_ID 129 
#define  U1_SP_ABSOLUTE_REPORT_ID 128 
 void* get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u1_raw_event(struct alps_dev *hdata, u8 *data, int size)
{
	unsigned int x, y, z;
	int i;
	short sp_x, sp_y;

	if (!data)
		return 0;
	switch (data[0]) {
	case U1_MOUSE_REPORT_ID:
		break;
	case U1_FEATURE_REPORT_ID:
		break;
	case U1_ABSOLUTE_REPORT_ID:
		for (i = 0; i < hdata->max_fingers; i++) {
			u8 *contact = &data[i * 5];

			x = get_unaligned_le16(contact + 3);
			y = get_unaligned_le16(contact + 5);
			z = contact[7] & 0x7F;

			input_mt_slot(hdata->input, i);

			if (z != 0) {
				input_mt_report_slot_state(hdata->input,
					MT_TOOL_FINGER, 1);
				input_report_abs(hdata->input,
					ABS_MT_POSITION_X, x);
				input_report_abs(hdata->input,
					ABS_MT_POSITION_Y, y);
				input_report_abs(hdata->input,
					ABS_MT_PRESSURE, z);
			} else {
				input_mt_report_slot_state(hdata->input,
					MT_TOOL_FINGER, 0);
			}
		}

		input_mt_sync_frame(hdata->input);

		input_report_key(hdata->input, BTN_LEFT,
			data[1] & 0x1);
		input_report_key(hdata->input, BTN_RIGHT,
			(data[1] & 0x2));
		input_report_key(hdata->input, BTN_MIDDLE,
			(data[1] & 0x4));

		input_sync(hdata->input);

		return 1;

	case U1_SP_ABSOLUTE_REPORT_ID:
		sp_x = get_unaligned_le16(data+2);
		sp_y = get_unaligned_le16(data+4);

		sp_x = sp_x / 8;
		sp_y = sp_y / 8;

		input_report_rel(hdata->input2, REL_X, sp_x);
		input_report_rel(hdata->input2, REL_Y, sp_y);

		input_report_key(hdata->input2, BTN_LEFT,
			data[1] & 0x1);
		input_report_key(hdata->input2, BTN_RIGHT,
			(data[1] & 0x2));
		input_report_key(hdata->input2, BTN_MIDDLE,
			(data[1] & 0x4));

		input_sync(hdata->input2);

		return 1;
	}

	return 0;
}