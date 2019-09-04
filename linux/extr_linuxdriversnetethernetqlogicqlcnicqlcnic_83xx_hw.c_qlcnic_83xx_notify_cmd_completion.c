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
struct qlcnic_cmd_args {scalar_t__ type; int /*<<< orphan*/  completion; int /*<<< orphan*/  rsp_status; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ QLC_83XX_MBX_CMD_NO_WAIT ; 
 int /*<<< orphan*/  QLC_83XX_MBX_RESPONSE_ARRIVED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 

__attribute__((used)) static inline void
qlcnic_83xx_notify_cmd_completion(struct qlcnic_adapter *adapter,
				  struct qlcnic_cmd_args *cmd)
{
	atomic_set(&cmd->rsp_status, QLC_83XX_MBX_RESPONSE_ARRIVED);

	if (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT) {
		qlcnic_free_mbx_args(cmd);
		kfree(cmd);
		return;
	}
	complete(&cmd->completion);
}