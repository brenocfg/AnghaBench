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
struct max11801_data {int /*<<< orphan*/  input_dev; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
#define  EVENT_FIFO_END 131 
#define  EVENT_INIT 130 
#define  EVENT_MIDDLE 129 
#define  EVENT_RELEASE 128 
 int EVENT_TAG_MASK ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  FIFO_RD_CMD ; 
 int /*<<< orphan*/  GENERNAL_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX11801_FIFO_INT ; 
 int MAX11801_FIFO_OVERFLOW ; 
 int MEASURE_TAG_MASK ; 
 int MEASURE_X_TAG ; 
 int MEASURE_Y_TAG ; 
 int XY_BUFSIZE ; 
 int XY_BUF_OFFSET ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int read_register (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max11801_ts_interrupt(int irq, void *dev_id)
{
	struct max11801_data *data = dev_id;
	struct i2c_client *client = data->client;
	int status, i, ret;
	u8 buf[XY_BUFSIZE];
	int x = -1;
	int y = -1;

	status = read_register(data->client, GENERNAL_STATUS_REG);

	if (status & (MAX11801_FIFO_INT | MAX11801_FIFO_OVERFLOW)) {
		status = read_register(data->client, GENERNAL_STATUS_REG);

		ret = i2c_smbus_read_i2c_block_data(client, FIFO_RD_CMD,
						    XY_BUFSIZE, buf);

		/*
		 * We should get 4 bytes buffer that contains X,Y
		 * and event tag
		 */
		if (ret < XY_BUFSIZE)
			goto out;

		for (i = 0; i < XY_BUFSIZE; i += XY_BUFSIZE / 2) {
			if ((buf[i + 1] & MEASURE_TAG_MASK) == MEASURE_X_TAG)
				x = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
			else if ((buf[i + 1] & MEASURE_TAG_MASK) == MEASURE_Y_TAG)
				y = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
		}

		if ((buf[1] & EVENT_TAG_MASK) != (buf[3] & EVENT_TAG_MASK))
			goto out;

		switch (buf[1] & EVENT_TAG_MASK) {
		case EVENT_INIT:
			/* fall through */
		case EVENT_MIDDLE:
			input_report_abs(data->input_dev, ABS_X, x);
			input_report_abs(data->input_dev, ABS_Y, y);
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 1);
			input_sync(data->input_dev);
			break;

		case EVENT_RELEASE:
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 0);
			input_sync(data->input_dev);
			break;

		case EVENT_FIFO_END:
			break;
		}
	}
out:
	return IRQ_HANDLED;
}