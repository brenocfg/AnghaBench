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
struct serio {int dummy; } ;
struct cec_msg {int len; int* msg; } ;
struct pulse8 {int started; int escape; scalar_t__ idx; int* buf; int* data; scalar_t__ len; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  work; struct cec_msg rx_msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CEC_MAX_MSG_SIZE ; 
 scalar_t__ DATA_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  MSGCODE_COMMAND_ACCEPTED 140 
#define  MSGCODE_COMMAND_REJECTED 139 
#define  MSGCODE_FRAME_DATA 138 
 int MSGCODE_FRAME_EOM ; 
#define  MSGCODE_FRAME_START 137 
#define  MSGCODE_HIGH_ERROR 136 
#define  MSGCODE_LOW_ERROR 135 
#define  MSGCODE_RECEIVE_FAILED 134 
#define  MSGCODE_TIMEOUT_ERROR 133 
#define  MSGCODE_TRANSMIT_FAILED_ACK 132 
#define  MSGCODE_TRANSMIT_FAILED_LINE 131 
#define  MSGCODE_TRANSMIT_FAILED_TIMEOUT_DATA 130 
#define  MSGCODE_TRANSMIT_FAILED_TIMEOUT_LINE 129 
#define  MSGCODE_TRANSMIT_SUCCEEDED 128 
 unsigned char MSGEND ; 
 unsigned char MSGESC ; 
 scalar_t__ MSGOFFSET ; 
 unsigned char MSGSTART ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct pulse8* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t pulse8_interrupt(struct serio *serio, unsigned char data,
				    unsigned int flags)
{
	struct pulse8 *pulse8 = serio_get_drvdata(serio);

	if (!pulse8->started && data != MSGSTART)
		return IRQ_HANDLED;
	if (data == MSGESC) {
		pulse8->escape = true;
		return IRQ_HANDLED;
	}
	if (pulse8->escape) {
		data += MSGOFFSET;
		pulse8->escape = false;
	} else if (data == MSGEND) {
		struct cec_msg *msg = &pulse8->rx_msg;

		if (debug)
			dev_info(pulse8->dev, "received: %*ph\n",
				 pulse8->idx, pulse8->buf);
		pulse8->data[0] = pulse8->buf[0];
		switch (pulse8->buf[0] & 0x3f) {
		case MSGCODE_FRAME_START:
			msg->len = 1;
			msg->msg[0] = pulse8->buf[1];
			break;
		case MSGCODE_FRAME_DATA:
			if (msg->len == CEC_MAX_MSG_SIZE)
				break;
			msg->msg[msg->len++] = pulse8->buf[1];
			if (pulse8->buf[0] & MSGCODE_FRAME_EOM)
				schedule_work(&pulse8->work);
			break;
		case MSGCODE_TRANSMIT_SUCCEEDED:
		case MSGCODE_TRANSMIT_FAILED_LINE:
		case MSGCODE_TRANSMIT_FAILED_ACK:
		case MSGCODE_TRANSMIT_FAILED_TIMEOUT_DATA:
		case MSGCODE_TRANSMIT_FAILED_TIMEOUT_LINE:
			schedule_work(&pulse8->work);
			break;
		case MSGCODE_HIGH_ERROR:
		case MSGCODE_LOW_ERROR:
		case MSGCODE_RECEIVE_FAILED:
		case MSGCODE_TIMEOUT_ERROR:
			break;
		case MSGCODE_COMMAND_ACCEPTED:
		case MSGCODE_COMMAND_REJECTED:
		default:
			if (pulse8->idx == 0)
				break;
			memcpy(pulse8->data, pulse8->buf, pulse8->idx);
			pulse8->len = pulse8->idx;
			complete(&pulse8->cmd_done);
			break;
		}
		pulse8->idx = 0;
		pulse8->started = false;
		return IRQ_HANDLED;
	} else if (data == MSGSTART) {
		pulse8->idx = 0;
		pulse8->started = true;
		return IRQ_HANDLED;
	}

	if (pulse8->idx >= DATA_SIZE) {
		dev_dbg(pulse8->dev,
			"throwing away %d bytes of garbage\n", pulse8->idx);
		pulse8->idx = 0;
	}
	pulse8->buf[pulse8->idx++] = data;
	return IRQ_HANDLED;
}