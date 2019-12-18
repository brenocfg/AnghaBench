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
struct pms7003_state {int /*<<< orphan*/  frame_ready; int /*<<< orphan*/  serdev; } ;
typedef  enum pms7003_cmd { ____Placeholder_pms7003_cmd } pms7003_cmd ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int PMS7003_CMD_LENGTH ; 
 int /*<<< orphan*/  PMS7003_TIMEOUT ; 
 int /*<<< orphan*/ * pms7003_cmd_tbl ; 
 int serdev_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pms7003_do_cmd(struct pms7003_state *state, enum pms7003_cmd cmd)
{
	int ret;

	ret = serdev_device_write(state->serdev, pms7003_cmd_tbl[cmd],
				  PMS7003_CMD_LENGTH, PMS7003_TIMEOUT);
	if (ret < PMS7003_CMD_LENGTH)
		return ret < 0 ? ret : -EIO;

	ret = wait_for_completion_interruptible_timeout(&state->frame_ready,
							PMS7003_TIMEOUT);
	if (!ret)
		ret = -ETIMEDOUT;

	return ret < 0 ? ret : 0;
}