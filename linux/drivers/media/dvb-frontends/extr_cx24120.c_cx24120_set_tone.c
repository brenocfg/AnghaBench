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
struct cx24120_state {TYPE_1__* i2c; } ;
struct cx24120_cmd {int len; int* arg; int /*<<< orphan*/  id; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SETTONE ; 
 int EINVAL ; 
 int SEC_TONE_OFF ; 
 int SEC_TONE_ON ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  err (char*,int) ; 

__attribute__((used)) static int cx24120_set_tone(struct dvb_frontend *fe, enum fe_sec_tone_mode tone)
{
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "(%d)\n", tone);

	if ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) {
		err("Invalid tone=%d\n", tone);
		return -EINVAL;
	}

	cmd.id = CMD_SETTONE;
	cmd.len = 4;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x00;
	cmd.arg[3] = (tone == SEC_TONE_ON) ? 0x01 : 0x00;

	return cx24120_message_send(state, &cmd);
}