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
typedef  unsigned int u8 ;
struct mip4_ts {int* buf; int /*<<< orphan*/  input; scalar_t__ event_size; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int MIP4_R0_EVENT ; 
 unsigned int MIP4_R1_EVENT_PACKET_DATA ; 
 unsigned int MIP4_R1_EVENT_PACKET_INFO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int mip4_handle_packet (struct mip4_ts*,int*) ; 
 int mip4_i2c_xfer (struct mip4_ts*,unsigned int*,int,int*,unsigned int) ; 

__attribute__((used)) static irqreturn_t mip4_interrupt(int irq, void *dev_id)
{
	struct mip4_ts *ts = dev_id;
	struct i2c_client *client = ts->client;
	unsigned int i;
	int error;
	u8 cmd[2];
	u8 size;
	bool alert;

	/* Read packet info */
	cmd[0] = MIP4_R0_EVENT;
	cmd[1] = MIP4_R1_EVENT_PACKET_INFO;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd), ts->buf, 1);
	if (error) {
		dev_err(&client->dev,
			"Failed to read packet info: %d\n", error);
		goto out;
	}

	size = ts->buf[0] & 0x7F;
	alert = ts->buf[0] & BIT(7);
	dev_dbg(&client->dev, "packet size: %d, alert: %d\n", size, alert);

	/* Check size */
	if (!size) {
		dev_err(&client->dev, "Empty packet\n");
		goto out;
	}

	/* Read packet data */
	cmd[0] = MIP4_R0_EVENT;
	cmd[1] = MIP4_R1_EVENT_PACKET_DATA;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd), ts->buf, size);
	if (error) {
		dev_err(&client->dev,
			"Failed to read packet data: %d\n", error);
		goto out;
	}

	if (alert) {
		dev_dbg(&client->dev, "Alert: %d\n", ts->buf[0]);
	} else {
		for (i = 0; i < size; i += ts->event_size) {
			error = mip4_handle_packet(ts, &ts->buf[i]);
			if (error)
				break;
		}

		input_sync(ts->input);
	}

out:
	return IRQ_HANDLED;
}