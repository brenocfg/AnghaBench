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
struct bnx2x_queue_state_params {int cmd; } ;
struct bnx2x_queue_sp_obj {int /*<<< orphan*/  pending; } ;
typedef  enum bnx2x_queue_cmd { ____Placeholder_bnx2x_queue_cmd } bnx2x_queue_cmd ;

/* Variables and functions */
 int BNX2X_Q_CMD_ACTIVATE ; 
 int BNX2X_Q_CMD_DEACTIVATE ; 
 int BNX2X_Q_CMD_UPDATE ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_queue_set_pending(struct bnx2x_queue_sp_obj *obj,
				   struct bnx2x_queue_state_params *params)
{
	enum bnx2x_queue_cmd cmd = params->cmd, bit;

	/* ACTIVATE and DEACTIVATE commands are implemented on top of
	 * UPDATE command.
	 */
	if ((cmd == BNX2X_Q_CMD_ACTIVATE) ||
	    (cmd == BNX2X_Q_CMD_DEACTIVATE))
		bit = BNX2X_Q_CMD_UPDATE;
	else
		bit = cmd;

	set_bit(bit, &obj->pending);
	return bit;
}