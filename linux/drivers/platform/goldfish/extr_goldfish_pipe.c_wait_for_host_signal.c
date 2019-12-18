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
typedef  int /*<<< orphan*/  u32 ;
struct goldfish_pipe {int /*<<< orphan*/  flags; int /*<<< orphan*/  wake_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CLOSED_ON_HOST ; 
 int /*<<< orphan*/  BIT_WAKE_ON_READ ; 
 int /*<<< orphan*/  BIT_WAKE_ON_WRITE ; 
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PIPE_CMD_WAKE_ON_READ ; 
 int /*<<< orphan*/  PIPE_CMD_WAKE_ON_WRITE ; 
 int /*<<< orphan*/  goldfish_pipe_cmd (struct goldfish_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wait_for_host_signal(struct goldfish_pipe *pipe, int is_write)
{
	u32 wake_bit = is_write ? BIT_WAKE_ON_WRITE : BIT_WAKE_ON_READ;

	set_bit(wake_bit, &pipe->flags);

	/* Tell the emulator we're going to wait for a wake event */
	goldfish_pipe_cmd(pipe,
		is_write ? PIPE_CMD_WAKE_ON_WRITE : PIPE_CMD_WAKE_ON_READ);

	while (test_bit(wake_bit, &pipe->flags)) {
		if (wait_event_interruptible(pipe->wake_queue,
					     !test_bit(wake_bit, &pipe->flags)))
			return -ERESTARTSYS;

		if (test_bit(BIT_CLOSED_ON_HOST, &pipe->flags))
			return -EIO;
	}

	return 0;
}