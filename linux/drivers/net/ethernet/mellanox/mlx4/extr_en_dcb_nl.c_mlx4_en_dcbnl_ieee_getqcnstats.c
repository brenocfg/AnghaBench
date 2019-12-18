#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int port; TYPE_2__* mdev; } ;
struct mlx4_congestion_control_mb_prio_802_1_qau_statistics {int /*<<< orphan*/  rppp_created_rps; int /*<<< orphan*/  rppp_rp_centiseconds; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; scalar_t__ buf; } ;
struct ieee_qcn_stats {int /*<<< orphan*/ * rppp_created_rps; int /*<<< orphan*/ * rppp_rp_centiseconds; } ;
struct TYPE_6__ {int flags2; } ;
struct TYPE_8__ {TYPE_1__ caps; } ;
struct TYPE_7__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_CONGESTION_CTRL_OPCODE ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_C ; 
 int /*<<< orphan*/  MLX4_CONGESTION_CONTROL_GET_STATISTICS ; 
 int MLX4_CTRL_ALGO_802_1_QAU_REACTION_POINT ; 
 int MLX4_DEV_CAP_FLAG2_QCN ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (TYPE_3__*) ; 
 int mlx4_cmd_box (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (TYPE_3__*,struct mlx4_cmd_mailbox*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_dcbnl_ieee_getqcnstats(struct net_device *dev,
					  struct ieee_qcn_stats *qcn_stats)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_congestion_control_mb_prio_802_1_qau_statistics *hw_qcn_stats;
	struct mlx4_cmd_mailbox *mailbox_out = NULL;
	u64 mailbox_in_dma = 0;
	u32 inmod = 0;
	int i, err;

	if (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QCN))
		return -EOPNOTSUPP;

	mailbox_out = mlx4_alloc_cmd_mailbox(priv->mdev->dev);
	if (IS_ERR(mailbox_out))
		return -ENOMEM;

	hw_qcn_stats =
	(struct mlx4_congestion_control_mb_prio_802_1_qau_statistics *)
	mailbox_out->buf;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		inmod = priv->port | ((1 << i) << 8) |
			 (MLX4_CTRL_ALGO_802_1_QAU_REACTION_POINT << 16);
		err = mlx4_cmd_box(priv->mdev->dev, mailbox_in_dma,
				   mailbox_out->dma, inmod,
				   MLX4_CONGESTION_CONTROL_GET_STATISTICS,
				   MLX4_CMD_CONGESTION_CTRL_OPCODE,
				   MLX4_CMD_TIME_CLASS_C,
				   MLX4_CMD_NATIVE);
		if (err) {
			mlx4_free_cmd_mailbox(priv->mdev->dev, mailbox_out);
			return err;
		}
		qcn_stats->rppp_rp_centiseconds[i] =
			be64_to_cpu(hw_qcn_stats->rppp_rp_centiseconds);
		qcn_stats->rppp_created_rps[i] =
			be32_to_cpu(hw_qcn_stats->rppp_created_rps);
	}
	mlx4_free_cmd_mailbox(priv->mdev->dev, mailbox_out);
	return 0;
}