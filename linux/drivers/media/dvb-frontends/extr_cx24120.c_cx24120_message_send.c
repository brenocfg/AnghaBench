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
struct cx24120_state {TYPE_1__* i2c; scalar_t__ mpeg_enabled; } ;
struct cx24120_cmd {int id; int /*<<< orphan*/  len; int /*<<< orphan*/ * arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX24120_REG_CMD_ARGS ; 
 int /*<<< orphan*/  CX24120_REG_CMD_END ; 
 int /*<<< orphan*/  CX24120_REG_CMD_START ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  cx24120_check_cmd (struct cx24120_state*,int) ; 
 scalar_t__ cx24120_readreg (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx24120_writereg (struct cx24120_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx24120_writeregs (struct cx24120_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cx24120_message_send(struct cx24120_state *state,
				struct cx24120_cmd *cmd)
{
	int ficus;

	if (state->mpeg_enabled) {
		/* Disable mpeg out on certain commands */
		cx24120_check_cmd(state, cmd->id);
	}

	cx24120_writereg(state, CX24120_REG_CMD_START, cmd->id);
	cx24120_writeregs(state, CX24120_REG_CMD_ARGS, &cmd->arg[0],
			  cmd->len, 1);
	cx24120_writereg(state, CX24120_REG_CMD_END, 0x01);

	ficus = 1000;
	while (cx24120_readreg(state, CX24120_REG_CMD_END)) {
		msleep(20);
		ficus -= 20;
		if (ficus == 0) {
			err("Error sending message to firmware\n");
			return -EREMOTEIO;
		}
	}
	dev_dbg(&state->i2c->dev, "sent message 0x%02x\n", cmd->id);

	return 0;
}