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
typedef  int u64 ;
struct mlx4_vhcr {int in_param; int out_param; int /*<<< orphan*/  op; int /*<<< orphan*/  op_modifier; int /*<<< orphan*/  in_modifier; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {scalar_t__ dma; } ;
struct mlx4_cmd_info {int /*<<< orphan*/  out_is_imm; scalar_t__ encode_slave_id; scalar_t__ has_outbox; scalar_t__ has_inbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int __mlx4_cmd (struct mlx4_dev*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_DMA_wrapper(struct mlx4_dev *dev, int slave,
		     struct mlx4_vhcr *vhcr,
		     struct mlx4_cmd_mailbox *inbox,
		     struct mlx4_cmd_mailbox *outbox,
		     struct mlx4_cmd_info *cmd)
{
	u64 in_param;
	u64 out_param;
	int err;

	in_param = cmd->has_inbox ? (u64) inbox->dma : vhcr->in_param;
	out_param = cmd->has_outbox ? (u64) outbox->dma : vhcr->out_param;
	if (cmd->encode_slave_id) {
		in_param &= 0xffffffffffffff00ll;
		in_param |= slave;
	}

	err = __mlx4_cmd(dev, in_param, &out_param, cmd->out_is_imm,
			 vhcr->in_modifier, vhcr->op_modifier, vhcr->op,
			 MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	if (cmd->out_is_imm)
		vhcr->out_param = out_param;

	return err;
}