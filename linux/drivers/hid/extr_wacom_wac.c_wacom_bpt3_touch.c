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
struct wacom_wac {unsigned char* data; TYPE_1__* shared; scalar_t__ touch_input; } ;
struct TYPE_2__ {int /*<<< orphan*/  touch_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_mt_sync_frame (scalar_t__) ; 
 int /*<<< orphan*/  wacom_bpt3_button_msg (struct wacom_wac*,unsigned char*) ; 
 int /*<<< orphan*/  wacom_bpt3_touch_msg (struct wacom_wac*,unsigned char*) ; 
 int /*<<< orphan*/  wacom_wac_finger_count_touches (struct wacom_wac*) ; 

__attribute__((used)) static int wacom_bpt3_touch(struct wacom_wac *wacom)
{
	unsigned char *data = wacom->data;
	int count = data[1] & 0x07;
	int  touch_changed = 0, i;

	if (data[0] != 0x02)
	    return 0;

	/* data has up to 7 fixed sized 8-byte messages starting at data[2] */
	for (i = 0; i < count; i++) {
		int offset = (8 * i) + 2;
		int msg_id = data[offset];

		if (msg_id >= 2 && msg_id <= 17) {
			wacom_bpt3_touch_msg(wacom, data + offset);
			touch_changed++;
		} else if (msg_id == 128)
			wacom_bpt3_button_msg(wacom, data + offset);

	}

	/* only update touch if we actually have a touchpad and touch data changed */
	if (wacom->touch_input && touch_changed) {
		input_mt_sync_frame(wacom->touch_input);
		wacom->shared->touch_down = wacom_wac_finger_count_touches(wacom);
	}

	return 1;
}