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
struct dvb_frontend {struct cx24120_state* demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; int /*<<< orphan*/  msg; } ;
struct cx24120_state {TYPE_1__* i2c; } ;
struct cx24120_cmd {int len; int* arg; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DISEQC_MSG1 ; 
 int /*<<< orphan*/  CMD_DISEQC_MSG2 ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 scalar_t__ cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 int cx24120_readreg (struct cx24120_state*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cx24120_send_diseqc_msg(struct dvb_frontend *fe,
				   struct dvb_diseqc_master_cmd *d)
{
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;
	int back_count;

	dev_dbg(&state->i2c->dev, "\n");

	cmd.id = CMD_DISEQC_MSG1;
	cmd.len = 11;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x03;
	cmd.arg[3] = 0x16;
	cmd.arg[4] = 0x28;
	cmd.arg[5] = 0x01;
	cmd.arg[6] = 0x01;
	cmd.arg[7] = 0x14;
	cmd.arg[8] = 0x19;
	cmd.arg[9] = 0x14;
	cmd.arg[10] = 0x1e;

	if (cx24120_message_send(state, &cmd)) {
		err("send 1st message(0x%x) failed\n", cmd.id);
		return -EREMOTEIO;
	}

	cmd.id = CMD_DISEQC_MSG2;
	cmd.len = d->msg_len + 6;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x01;
	cmd.arg[2] = 0x02;
	cmd.arg[3] = 0x00;
	cmd.arg[4] = 0x00;
	cmd.arg[5] = d->msg_len;

	memcpy(&cmd.arg[6], &d->msg, d->msg_len);

	if (cx24120_message_send(state, &cmd)) {
		err("send 2nd message(0x%x) failed\n", cmd.id);
		return -EREMOTEIO;
	}

	back_count = 500;
	do {
		if (!(cx24120_readreg(state, 0x93) & 0x01)) {
			dev_dbg(&state->i2c->dev, "diseqc sequence sent\n");
			return 0;
		}
		msleep(20);
		back_count -= 20;
	} while (back_count);

	err("Too long waiting for diseqc.\n");
	return -ETIMEDOUT;
}