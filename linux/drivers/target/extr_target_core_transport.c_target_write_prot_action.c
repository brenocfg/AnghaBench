#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct se_cmd {int prot_op; int data_length; int /*<<< orphan*/  pi_err; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  transport_state; int /*<<< orphan*/  t_prot_sg; int /*<<< orphan*/  t_task_lba; TYPE_3__* se_dev; TYPE_1__* se_sess; } ;
struct TYPE_5__ {int /*<<< orphan*/  block_size; } ;
struct TYPE_6__ {TYPE_2__ dev_attrib; } ;
struct TYPE_4__ {int const sup_prot_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_T_SENT ; 
#define  TARGET_PROT_DOUT_INSERT 129 
#define  TARGET_PROT_DOUT_STRIP 128 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbc_dif_generate (struct se_cmd*) ; 
 int /*<<< orphan*/  sbc_dif_verify (struct se_cmd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_generic_request_failure (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int target_write_prot_action(struct se_cmd *cmd)
{
	u32 sectors;
	/*
	 * Perform WRITE_INSERT of PI using software emulation when backend
	 * device has PI enabled, if the transport has not already generated
	 * PI using hardware WRITE_INSERT offload.
	 */
	switch (cmd->prot_op) {
	case TARGET_PROT_DOUT_INSERT:
		if (!(cmd->se_sess->sup_prot_ops & TARGET_PROT_DOUT_INSERT))
			sbc_dif_generate(cmd);
		break;
	case TARGET_PROT_DOUT_STRIP:
		if (cmd->se_sess->sup_prot_ops & TARGET_PROT_DOUT_STRIP)
			break;

		sectors = cmd->data_length >> ilog2(cmd->se_dev->dev_attrib.block_size);
		cmd->pi_err = sbc_dif_verify(cmd, cmd->t_task_lba,
					     sectors, 0, cmd->t_prot_sg, 0);
		if (unlikely(cmd->pi_err)) {
			spin_lock_irq(&cmd->t_state_lock);
			cmd->transport_state &= ~CMD_T_SENT;
			spin_unlock_irq(&cmd->t_state_lock);
			transport_generic_request_failure(cmd, cmd->pi_err);
			return -1;
		}
		break;
	default:
		break;
	}

	return 0;
}