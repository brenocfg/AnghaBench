#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_reg_trans {int /*<<< orphan*/  timeout_dw; TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  emad_wq; scalar_t__ fw_flash_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_EMAD_TIMEOUT_DURING_FW_FLASH_MS ; 
 int /*<<< orphan*/  MLXSW_EMAD_TIMEOUT_MS ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mlxsw_emad_trans_timeout_schedule(struct mlxsw_reg_trans *trans)
{
	unsigned long timeout = msecs_to_jiffies(MLXSW_EMAD_TIMEOUT_MS);

	if (trans->core->fw_flash_in_progress)
		timeout = msecs_to_jiffies(MLXSW_EMAD_TIMEOUT_DURING_FW_FLASH_MS);

	queue_delayed_work(trans->core->emad_wq, &trans->timeout_dw, timeout);
}