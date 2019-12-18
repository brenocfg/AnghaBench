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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct mlx4_vhcr {int /*<<< orphan*/  in_modifier; } ;
struct mlx4_ptys_reg {int /*<<< orphan*/  local_port; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; struct mlx4_access_reg* buf; } ;
struct mlx4_cmd_info {int dummy; } ;
struct mlx4_access_reg {scalar_t__ method; scalar_t__ reg_data; int /*<<< orphan*/  reg_id; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ MLX4_ACCESS_REG_METHOD_MASK ; 
 scalar_t__ MLX4_ACCESS_REG_WRITE ; 
 int /*<<< orphan*/  MLX4_CMD_ACCESS_REG ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_C ; 
 scalar_t__ MLX4_REG_ID_PTYS ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_slave_convert_port (struct mlx4_dev*,int,int /*<<< orphan*/ ) ; 

int mlx4_ACCESS_REG_wrapper(struct mlx4_dev *dev, int slave,
			    struct mlx4_vhcr *vhcr,
			    struct mlx4_cmd_mailbox *inbox,
			    struct mlx4_cmd_mailbox *outbox,
			    struct mlx4_cmd_info *cmd)
{
	struct mlx4_access_reg *inbuf = inbox->buf;
	u8 method = inbuf->method & MLX4_ACCESS_REG_METHOD_MASK;
	u16 reg_id = be16_to_cpu(inbuf->reg_id);

	if (slave != mlx4_master_func_num(dev) &&
	    method == MLX4_ACCESS_REG_WRITE)
		return -EPERM;

	if (reg_id == MLX4_REG_ID_PTYS) {
		struct mlx4_ptys_reg *ptys_reg =
			(struct mlx4_ptys_reg *)inbuf->reg_data;

		ptys_reg->local_port =
			mlx4_slave_convert_port(dev, slave,
						ptys_reg->local_port);
	}

	return mlx4_cmd_box(dev, inbox->dma, outbox->dma, vhcr->in_modifier,
			    0, MLX4_CMD_ACCESS_REG, MLX4_CMD_TIME_CLASS_C,
			    MLX4_CMD_NATIVE);
}