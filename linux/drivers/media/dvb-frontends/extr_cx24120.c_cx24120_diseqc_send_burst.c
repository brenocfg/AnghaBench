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
struct cx24120_cmd {int* arg; scalar_t__ len; int /*<<< orphan*/  id; } ;
typedef  enum fe_sec_mini_cmd { ____Placeholder_fe_sec_mini_cmd } fe_sec_mini_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DISEQC_BURST ; 
 int SEC_MINI_B ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int cx24120_diseqc_send_burst(struct dvb_frontend *fe,
				     enum fe_sec_mini_cmd burst)
{
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "\n");

	/*
	 * Yes, cmd.len is set to zero. The old driver
	 * didn't specify any len, but also had a
	 * memset 0 before every use of the cmd struct
	 * which would have set it to zero.
	 * This quite probably needs looking into.
	 */
	cmd.id = CMD_DISEQC_BURST;
	cmd.len = 0;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = (burst == SEC_MINI_B) ? 0x01 : 0x00;

	return cx24120_message_send(state, &cmd);
}