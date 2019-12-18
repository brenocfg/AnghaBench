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
struct iscsi_cmd {int /*<<< orphan*/  dataout_timeout_lock; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsit_set_dataout_sequence_values (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  iscsit_start_dataout_timer (struct iscsi_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_set_unsolicited_dataout(struct iscsi_cmd *cmd)
{
	iscsit_set_dataout_sequence_values(cmd);

	spin_lock_bh(&cmd->dataout_timeout_lock);
	iscsit_start_dataout_timer(cmd, cmd->conn);
	spin_unlock_bh(&cmd->dataout_timeout_lock);
}