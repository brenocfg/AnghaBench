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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tcs_cmd {int wait; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_TCS_CMD (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_TCS_CMD_VOTE_MASK ; 

inline void tcs_cmd_gen(struct tcs_cmd *cmd, u64 vote_x, u64 vote_y,
			u32 addr, bool commit)
{
	bool valid = true;

	if (!cmd)
		return;

	if (vote_x == 0 && vote_y == 0)
		valid = false;

	if (vote_x > BCM_TCS_CMD_VOTE_MASK)
		vote_x = BCM_TCS_CMD_VOTE_MASK;

	if (vote_y > BCM_TCS_CMD_VOTE_MASK)
		vote_y = BCM_TCS_CMD_VOTE_MASK;

	cmd->addr = addr;
	cmd->data = BCM_TCS_CMD(commit, valid, vote_x, vote_y);

	/*
	 * Set the wait for completion flag on command that need to be completed
	 * before the next command.
	 */
	if (commit)
		cmd->wait = true;
}