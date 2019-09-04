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
struct cx24120_state {int dummy; } ;
struct cx24120_cmd {scalar_t__ len; int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int CX24120_MAX_CMD_LEN ; 
 int EREMOTEIO ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 int /*<<< orphan*/  cx24120_readreg (struct cx24120_state*,scalar_t__) ; 
 int /*<<< orphan*/  err (char*,int) ; 

__attribute__((used)) static int cx24120_message_sendrcv(struct cx24120_state *state,
				   struct cx24120_cmd *cmd, u8 numreg)
{
	int ret, i;

	if (numreg > CX24120_MAX_CMD_LEN) {
		err("Too many registers to read. cmd->reg = %d", numreg);
		return -EREMOTEIO;
	}

	ret = cx24120_message_send(state, cmd);
	if (ret != 0)
		return ret;

	if (!numreg)
		return 0;

	/* Read numreg registers starting from register cmd->len */
	for (i = 0; i < numreg; i++)
		cmd->arg[i] = cx24120_readreg(state, (cmd->len + i + 1));

	return 0;
}