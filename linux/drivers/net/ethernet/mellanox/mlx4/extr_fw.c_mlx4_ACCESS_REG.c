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
typedef  int u16 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; struct mlx4_access_reg* buf; } ;
struct mlx4_access_reg {int constant2; int method; void* reg_data; int status; void* len_const; void* reg_id; void* constant1; } ;
typedef  enum mlx4_access_reg_method { ____Placeholder_mlx4_access_reg_method } mlx4_access_reg_method ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int MLX4_ACCESS_REG_LEN_MASK ; 
 int MLX4_ACCESS_REG_METHOD_MASK ; 
 int MLX4_ACCESS_REG_STATUS_MASK ; 
 int /*<<< orphan*/  MLX4_CMD_ACCESS_REG ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_C ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int min (int,int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

__attribute__((used)) static int mlx4_ACCESS_REG(struct mlx4_dev *dev, u16 reg_id,
			   enum mlx4_access_reg_method method,
			   u16 reg_len, void *reg_data)
{
	struct mlx4_cmd_mailbox *inbox, *outbox;
	struct mlx4_access_reg *inbuf, *outbuf;
	int err;

	inbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(inbox))
		return PTR_ERR(inbox);

	outbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(outbox)) {
		mlx4_free_cmd_mailbox(dev, inbox);
		return PTR_ERR(outbox);
	}

	inbuf = inbox->buf;
	outbuf = outbox->buf;

	inbuf->constant1 = cpu_to_be16(0x1<<11 | 0x4);
	inbuf->constant2 = 0x1;
	inbuf->reg_id = cpu_to_be16(reg_id);
	inbuf->method = method & MLX4_ACCESS_REG_METHOD_MASK;

	reg_len = min(reg_len, (u16)(sizeof(inbuf->reg_data)));
	inbuf->len_const =
		cpu_to_be16(((reg_len/4 + 1) & MLX4_ACCESS_REG_LEN_MASK) |
			    ((0x3) << 12));

	memcpy(inbuf->reg_data, reg_data, reg_len);
	err = mlx4_cmd_box(dev, inbox->dma, outbox->dma, 0, 0,
			   MLX4_CMD_ACCESS_REG, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_WRAPPED);
	if (err)
		goto out;

	if (outbuf->status & MLX4_ACCESS_REG_STATUS_MASK) {
		err = outbuf->status & MLX4_ACCESS_REG_STATUS_MASK;
		mlx4_err(dev,
			 "MLX4_CMD_ACCESS_REG(%x) returned REG status (%x)\n",
			 reg_id, err);
		goto out;
	}

	memcpy(reg_data, outbuf->reg_data, reg_len);
out:
	mlx4_free_cmd_mailbox(dev, inbox);
	mlx4_free_cmd_mailbox(dev, outbox);
	return err;
}