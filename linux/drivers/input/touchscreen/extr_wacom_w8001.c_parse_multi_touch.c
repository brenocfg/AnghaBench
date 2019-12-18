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
struct w8001 {unsigned char* data; scalar_t__ type; struct input_dev* touch_dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 scalar_t__ BTN_TOOL_FINGER ; 
 scalar_t__ BTN_TOOL_PEN ; 
 scalar_t__ BTN_TOOL_RUBBER ; 
 scalar_t__ KEY_RESERVED ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  scale_touch_coordinates (struct w8001*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void parse_multi_touch(struct w8001 *w8001)
{
	struct input_dev *dev = w8001->touch_dev;
	unsigned char *data = w8001->data;
	unsigned int x, y;
	int i;
	int count = 0;

	for (i = 0; i < 2; i++) {
		bool touch = data[0] & (1 << i);

		input_mt_slot(dev, i);
		input_mt_report_slot_state(dev, MT_TOOL_FINGER, touch);
		if (touch) {
			x = (data[6 * i + 1] << 7) | data[6 * i + 2];
			y = (data[6 * i + 3] << 7) | data[6 * i + 4];
			/* data[5,6] and [11,12] is finger capacity */

			/* scale to pen maximum */
			scale_touch_coordinates(w8001, &x, &y);

			input_report_abs(dev, ABS_MT_POSITION_X, x);
			input_report_abs(dev, ABS_MT_POSITION_Y, y);
			count++;
		}
	}

	/* emulate single touch events when stylus is out of proximity.
	 * This is to make single touch backward support consistent
	 * across all Wacom single touch devices.
	 */
	if (w8001->type != BTN_TOOL_PEN &&
			    w8001->type != BTN_TOOL_RUBBER) {
		w8001->type = count == 1 ? BTN_TOOL_FINGER : KEY_RESERVED;
		input_mt_report_pointer_emulation(dev, true);
	}

	input_sync(dev);
}