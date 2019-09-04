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
struct input_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct egalax_ts {struct i2c_client* client; struct input_dev* input_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  EGALAX_MAX_TRIES ; 
 int EVENT_DOWN_UP ; 
 int EVENT_ID_MASK ; 
 int EVENT_ID_OFFSET ; 
 int EVENT_VALID_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX_I2C_DATA_LEN ; 
 int MAX_SUPPORT_POINTS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int REPORT_MODE_MTTOUCH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t egalax_ts_interrupt(int irq, void *dev_id)
{
	struct egalax_ts *ts = dev_id;
	struct input_dev *input_dev = ts->input_dev;
	struct i2c_client *client = ts->client;
	u8 buf[MAX_I2C_DATA_LEN];
	int id, ret, x, y, z;
	int tries = 0;
	bool down, valid;
	u8 state;

	do {
		ret = i2c_master_recv(client, buf, MAX_I2C_DATA_LEN);
	} while (ret == -EAGAIN && tries++ < EGALAX_MAX_TRIES);

	if (ret < 0)
		return IRQ_HANDLED;

	if (buf[0] != REPORT_MODE_MTTOUCH) {
		/* ignore mouse events and vendor events */
		return IRQ_HANDLED;
	}

	state = buf[1];
	x = (buf[3] << 8) | buf[2];
	y = (buf[5] << 8) | buf[4];
	z = (buf[7] << 8) | buf[6];

	valid = state & EVENT_VALID_MASK;
	id = (state & EVENT_ID_MASK) >> EVENT_ID_OFFSET;
	down = state & EVENT_DOWN_UP;

	if (!valid || id > MAX_SUPPORT_POINTS) {
		dev_dbg(&client->dev, "point invalid\n");
		return IRQ_HANDLED;
	}

	input_mt_slot(input_dev, id);
	input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, down);

	dev_dbg(&client->dev, "%s id:%d x:%d y:%d z:%d",
		down ? "down" : "up", id, x, y, z);

	if (down) {
		input_report_abs(input_dev, ABS_MT_POSITION_X, x);
		input_report_abs(input_dev, ABS_MT_POSITION_Y, y);
		input_report_abs(input_dev, ABS_MT_PRESSURE, z);
	}

	input_mt_report_pointer_emulation(input_dev, true);
	input_sync(input_dev);

	return IRQ_HANDLED;
}