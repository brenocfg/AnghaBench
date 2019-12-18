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
struct iscsi_cmd {int /*<<< orphan*/  r2t_lock; } ;

/* Variables and functions */
 int iscsit_add_r2t_to_list (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_send_recovery_r2t(
	struct iscsi_cmd *cmd,
	u32 offset,
	u32 xfer_len)
{
	int ret;

	spin_lock_bh(&cmd->r2t_lock);
	ret = iscsit_add_r2t_to_list(cmd, offset, xfer_len, 1, 0);
	spin_unlock_bh(&cmd->r2t_lock);

	return ret;
}