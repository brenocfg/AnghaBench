#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct ps2dev {int flags; unsigned int cmdcnt; unsigned int* cmdbuf; int /*<<< orphan*/  nak; TYPE_1__* serio; int /*<<< orphan*/  wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EPROTO ; 
 unsigned int PS2_CMD_GETID ; 
 unsigned int PS2_CMD_RESET_BAT ; 
 int PS2_FLAG_ACK_CMD ; 
 int PS2_FLAG_CMD ; 
 int PS2_FLAG_CMD1 ; 
 int PS2_FLAG_WAITID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int*,int /*<<< orphan*/ ,int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,unsigned int) ; 
 unsigned int msecs_to_jiffies (int) ; 
 unsigned int ps2_adjust_timeout (struct ps2dev*,unsigned int,unsigned int) ; 
 int ps2_do_sendbyte (struct ps2dev*,unsigned int,int,int) ; 
 int /*<<< orphan*/  serio_continue_rx (TYPE_1__*) ; 
 int /*<<< orphan*/  serio_pause_rx (TYPE_1__*) ; 
 unsigned int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned int) ; 

int __ps2_command(struct ps2dev *ps2dev, u8 *param, unsigned int command)
{
	unsigned int timeout;
	unsigned int send = (command >> 12) & 0xf;
	unsigned int receive = (command >> 8) & 0xf;
	int rc;
	int i;
	u8 send_param[16];

	if (receive > sizeof(ps2dev->cmdbuf)) {
		WARN_ON(1);
		return -EINVAL;
	}

	if (send && !param) {
		WARN_ON(1);
		return -EINVAL;
	}

	memcpy(send_param, param, send);

	serio_pause_rx(ps2dev->serio);

	ps2dev->flags = command == PS2_CMD_GETID ? PS2_FLAG_WAITID : 0;
	ps2dev->cmdcnt = receive;
	if (receive && param)
		for (i = 0; i < receive; i++)
			ps2dev->cmdbuf[(receive - 1) - i] = param[i];

	/* Signal that we are sending the command byte */
	ps2dev->flags |= PS2_FLAG_ACK_CMD;

	/*
	 * Some devices (Synaptics) peform the reset before
	 * ACKing the reset command, and so it can take a long
	 * time before the ACK arrives.
	 */
	timeout = command == PS2_CMD_RESET_BAT ? 1000 : 200;

	rc = ps2_do_sendbyte(ps2dev, command & 0xff, timeout, 2);
	if (rc)
		goto out_reset_flags;

	/* Now we are sending command parameters, if any */
	ps2dev->flags &= ~PS2_FLAG_ACK_CMD;

	for (i = 0; i < send; i++) {
		rc = ps2_do_sendbyte(ps2dev, param[i], 200, 2);
		if (rc)
			goto out_reset_flags;
	}

	serio_continue_rx(ps2dev->serio);

	/*
	 * The reset command takes a long time to execute.
	 */
	timeout = msecs_to_jiffies(command == PS2_CMD_RESET_BAT ? 4000 : 500);

	timeout = wait_event_timeout(ps2dev->wait,
				     !(ps2dev->flags & PS2_FLAG_CMD1), timeout);

	if (ps2dev->cmdcnt && !(ps2dev->flags & PS2_FLAG_CMD1)) {

		timeout = ps2_adjust_timeout(ps2dev, command, timeout);
		wait_event_timeout(ps2dev->wait,
				   !(ps2dev->flags & PS2_FLAG_CMD), timeout);
	}

	serio_pause_rx(ps2dev->serio);

	if (param)
		for (i = 0; i < receive; i++)
			param[i] = ps2dev->cmdbuf[(receive - 1) - i];

	if (ps2dev->cmdcnt &&
	    (command != PS2_CMD_RESET_BAT || ps2dev->cmdcnt != 1)) {
		rc = -EPROTO;
		goto out_reset_flags;
	}

	rc = 0;

 out_reset_flags:
	ps2dev->flags = 0;
	serio_continue_rx(ps2dev->serio);

	dev_dbg(&ps2dev->serio->dev,
		"%02x [%*ph] - %x/%08lx [%*ph]\n",
		command & 0xff, send, send_param,
		ps2dev->nak, ps2dev->flags,
		receive, param ?: send_param);

	/*
	 * ps_command() handles resends itself, so do not leak -EAGAIN
	 * to the callers.
	 */
	return rc != -EAGAIN ? rc : -EPROTO;
}