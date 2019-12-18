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
struct mlx4_mod_stat_cfg {int /*<<< orphan*/  log_pg_sz_m; int /*<<< orphan*/  log_pg_sz; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_MOD_STAT_CFG ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_PUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_STAT_CFG_PG_SZ_M_OFFSET ; 
 int /*<<< orphan*/  MOD_STAT_CFG_PG_SZ_OFFSET ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_MOD_STAT_CFG(struct mlx4_dev *dev, struct mlx4_mod_stat_cfg *cfg)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32 *inbox;
	int err = 0;

#define MOD_STAT_CFG_IN_SIZE		0x100

#define MOD_STAT_CFG_PG_SZ_M_OFFSET	0x002
#define MOD_STAT_CFG_PG_SZ_OFFSET	0x003

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	inbox = mailbox->buf;

	MLX4_PUT(inbox, cfg->log_pg_sz, MOD_STAT_CFG_PG_SZ_OFFSET);
	MLX4_PUT(inbox, cfg->log_pg_sz_m, MOD_STAT_CFG_PG_SZ_M_OFFSET);

	err = mlx4_cmd(dev, mailbox->dma, 0, 0, MLX4_CMD_MOD_STAT_CFG,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}