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
typedef  int u8 ;
struct mxt_data {int T9_reportid_min; int max_x; int max_y; int update_input; struct input_dev* input_dev; TYPE_1__* client; } ;
struct input_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int MXT_PRESSURE_DEFAULT ; 
 int MXT_T9_AMP ; 
 int MXT_T9_DETECT ; 
 int MXT_T9_MOVE ; 
 int MXT_T9_PRESS ; 
 int MXT_T9_RELEASE ; 
 int MXT_T9_SUPPRESS ; 
 int MXT_T9_UNGRIP ; 
 int MXT_T9_VECTOR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,char,char,char,char,char,char,char,unsigned char,int,int,int,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxt_input_sync (struct mxt_data*) ; 

__attribute__((used)) static void mxt_proc_t9_message(struct mxt_data *data, u8 *message)
{
	struct device *dev = &data->client->dev;
	struct input_dev *input_dev = data->input_dev;
	int id;
	u8 status;
	int x;
	int y;
	int area;
	int amplitude;

	id = message[0] - data->T9_reportid_min;
	status = message[1];
	x = (message[2] << 4) | ((message[4] >> 4) & 0xf);
	y = (message[3] << 4) | ((message[4] & 0xf));

	/* Handle 10/12 bit switching */
	if (data->max_x < 1024)
		x >>= 2;
	if (data->max_y < 1024)
		y >>= 2;

	area = message[5];
	amplitude = message[6];

	dev_dbg(dev,
		"[%u] %c%c%c%c%c%c%c%c x: %5u y: %5u area: %3u amp: %3u\n",
		id,
		(status & MXT_T9_DETECT) ? 'D' : '.',
		(status & MXT_T9_PRESS) ? 'P' : '.',
		(status & MXT_T9_RELEASE) ? 'R' : '.',
		(status & MXT_T9_MOVE) ? 'M' : '.',
		(status & MXT_T9_VECTOR) ? 'V' : '.',
		(status & MXT_T9_AMP) ? 'A' : '.',
		(status & MXT_T9_SUPPRESS) ? 'S' : '.',
		(status & MXT_T9_UNGRIP) ? 'U' : '.',
		x, y, area, amplitude);

	input_mt_slot(input_dev, id);

	if (status & MXT_T9_DETECT) {
		/*
		 * Multiple bits may be set if the host is slow to read
		 * the status messages, indicating all the events that
		 * have happened.
		 */
		if (status & MXT_T9_RELEASE) {
			input_mt_report_slot_state(input_dev,
						   MT_TOOL_FINGER, 0);
			mxt_input_sync(data);
		}

		/* if active, pressure must be non-zero */
		if (!amplitude)
			amplitude = MXT_PRESSURE_DEFAULT;

		/* Touch active */
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 1);
		input_report_abs(input_dev, ABS_MT_POSITION_X, x);
		input_report_abs(input_dev, ABS_MT_POSITION_Y, y);
		input_report_abs(input_dev, ABS_MT_PRESSURE, amplitude);
		input_report_abs(input_dev, ABS_MT_TOUCH_MAJOR, area);
	} else {
		/* Touch no longer active, close out slot */
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 0);
	}

	data->update_input = true;
}