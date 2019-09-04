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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; scalar_t__* buf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_DIAG_RPRT ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_GET (scalar_t__,scalar_t__*,scalar_t__ const) ; 
 scalar_t__ const MLX4_MAILBOX_SIZE ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_query_diag_counters(struct mlx4_dev *dev, u8 op_modifier,
			     const u32 offset[],
			     u32 value[], size_t array_len, u8 port)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	size_t i;
	int ret;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	outbox = mailbox->buf;

	ret = mlx4_cmd_box(dev, 0, mailbox->dma, port, op_modifier,
			   MLX4_CMD_DIAG_RPRT, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	if (ret)
		goto out;

	for (i = 0; i < array_len; i++) {
		if (offset[i] > MLX4_MAILBOX_SIZE) {
			ret = -EINVAL;
			goto out;
		}

		MLX4_GET(value[i], outbox, offset[i]);
	}

out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return ret;
}