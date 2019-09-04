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
struct command {scalar_t__ status; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ IBMASM_CMD_COMPLETE ; 
 scalar_t__ IBMASM_CMD_FAILED ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

void ibmasm_wait_for_response(struct command *cmd, int timeout)
{
	wait_event_interruptible_timeout(cmd->wait,
				cmd->status == IBMASM_CMD_COMPLETE ||
				cmd->status == IBMASM_CMD_FAILED,
				timeout * HZ);
}