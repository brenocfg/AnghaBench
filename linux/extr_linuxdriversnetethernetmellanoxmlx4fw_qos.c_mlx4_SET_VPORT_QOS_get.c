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
typedef  int u8 ;
struct mlx4_vport_qos_param {int bw_share; int max_avg_bw; int enable; } ;
struct mlx4_set_vport_context {TYPE_1__* qos_p_up; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; struct mlx4_set_vport_context* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable; int /*<<< orphan*/  max_avg_bw; int /*<<< orphan*/  bw_share; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_SET_VPORT_QOS ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int MLX4_NUM_UP ; 
 int /*<<< orphan*/  MLX4_SET_VPORT_QOS_QUERY ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_SET_VPORT_QOS_get(struct mlx4_dev *dev, u8 port, u8 vport,
			   struct mlx4_vport_qos_param *out_param)
{
	int i;
	int err;
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_set_vport_context *ctx;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	ctx = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, (vport << 8) | port,
			   MLX4_SET_VPORT_QOS_QUERY,
			   MLX4_CMD_SET_VPORT_QOS,
			   MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	if (err)
		goto out;

	for (i = 0; i < MLX4_NUM_UP; i++) {
		out_param[i].bw_share = be32_to_cpu(ctx->qos_p_up[i].bw_share);
		out_param[i].max_avg_bw =
			be32_to_cpu(ctx->qos_p_up[i].max_avg_bw);
		out_param[i].enable =
			!!(be32_to_cpu(ctx->qos_p_up[i].enable) & 31);
	}

out:
	mlx4_free_cmd_mailbox(dev, mailbox);

	return err;
}