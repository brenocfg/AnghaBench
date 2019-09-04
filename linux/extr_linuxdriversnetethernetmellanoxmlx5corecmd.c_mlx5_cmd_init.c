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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct mlx5_cmd {int log_sz; int log_stride; int checksum_disabled; int max_reg_cmds; unsigned long bitmask; int cmdif_rev; int /*<<< orphan*/  pool; int /*<<< orphan*/  wq; int /*<<< orphan*/  wq_name; int /*<<< orphan*/  mode; scalar_t__ dma; int /*<<< orphan*/  pages_sem; int /*<<< orphan*/  sem; TYPE_3__* stats; int /*<<< orphan*/  token_lock; int /*<<< orphan*/  alloc_lock; } ;
struct mlx5_core_dev {TYPE_2__* pdev; TYPE_1__* iseg; struct mlx5_cmd cmd; } ;
struct mlx5_cmd_prot_block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmdq_addr_l_sz; int /*<<< orphan*/  cmdq_addr_h; int /*<<< orphan*/  cmdif_rev_fw_sub; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int CMD_IF_REV ; 
 int /*<<< orphan*/  CMD_MODE_POLLING ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int MLX5_ADAPTER_PAGE_SHIFT ; 
 int MLX5_MAX_COMMANDS ; 
 int alloc_cmd_page (struct mlx5_core_dev*,struct mlx5_cmd*) ; 
 int cmdif_rev (struct mlx5_core_dev*) ; 
 int create_debugfs_files (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  create_msg_cache (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_msg_cache (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd_page (struct mlx5_core_dev*,struct mlx5_cmd*) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mlx5_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,unsigned long long) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_wqname (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int mlx5_cmd_init(struct mlx5_core_dev *dev)
{
	int size = sizeof(struct mlx5_cmd_prot_block);
	int align = roundup_pow_of_two(size);
	struct mlx5_cmd *cmd = &dev->cmd;
	u32 cmd_h, cmd_l;
	u16 cmd_if_rev;
	int err;
	int i;

	memset(cmd, 0, sizeof(*cmd));
	cmd_if_rev = cmdif_rev(dev);
	if (cmd_if_rev != CMD_IF_REV) {
		dev_err(&dev->pdev->dev,
			"Driver cmdif rev(%d) differs from firmware's(%d)\n",
			CMD_IF_REV, cmd_if_rev);
		return -EINVAL;
	}

	cmd->pool = dma_pool_create("mlx5_cmd", &dev->pdev->dev, size, align,
				    0);
	if (!cmd->pool)
		return -ENOMEM;

	err = alloc_cmd_page(dev, cmd);
	if (err)
		goto err_free_pool;

	cmd_l = ioread32be(&dev->iseg->cmdq_addr_l_sz) & 0xff;
	cmd->log_sz = cmd_l >> 4 & 0xf;
	cmd->log_stride = cmd_l & 0xf;
	if (1 << cmd->log_sz > MLX5_MAX_COMMANDS) {
		dev_err(&dev->pdev->dev, "firmware reports too many outstanding commands %d\n",
			1 << cmd->log_sz);
		err = -EINVAL;
		goto err_free_page;
	}

	if (cmd->log_sz + cmd->log_stride > MLX5_ADAPTER_PAGE_SHIFT) {
		dev_err(&dev->pdev->dev, "command queue size overflow\n");
		err = -EINVAL;
		goto err_free_page;
	}

	cmd->checksum_disabled = 1;
	cmd->max_reg_cmds = (1 << cmd->log_sz) - 1;
	cmd->bitmask = (1UL << cmd->max_reg_cmds) - 1;

	cmd->cmdif_rev = ioread32be(&dev->iseg->cmdif_rev_fw_sub) >> 16;
	if (cmd->cmdif_rev > CMD_IF_REV) {
		dev_err(&dev->pdev->dev, "driver does not support command interface version. driver %d, firmware %d\n",
			CMD_IF_REV, cmd->cmdif_rev);
		err = -EOPNOTSUPP;
		goto err_free_page;
	}

	spin_lock_init(&cmd->alloc_lock);
	spin_lock_init(&cmd->token_lock);
	for (i = 0; i < ARRAY_SIZE(cmd->stats); i++)
		spin_lock_init(&cmd->stats[i].lock);

	sema_init(&cmd->sem, cmd->max_reg_cmds);
	sema_init(&cmd->pages_sem, 1);

	cmd_h = (u32)((u64)(cmd->dma) >> 32);
	cmd_l = (u32)(cmd->dma);
	if (cmd_l & 0xfff) {
		dev_err(&dev->pdev->dev, "invalid command queue address\n");
		err = -ENOMEM;
		goto err_free_page;
	}

	iowrite32be(cmd_h, &dev->iseg->cmdq_addr_h);
	iowrite32be(cmd_l, &dev->iseg->cmdq_addr_l_sz);

	/* Make sure firmware sees the complete address before we proceed */
	wmb();

	mlx5_core_dbg(dev, "descriptor at dma 0x%llx\n", (unsigned long long)(cmd->dma));

	cmd->mode = CMD_MODE_POLLING;

	create_msg_cache(dev);

	set_wqname(dev);
	cmd->wq = create_singlethread_workqueue(cmd->wq_name);
	if (!cmd->wq) {
		dev_err(&dev->pdev->dev, "failed to create command workqueue\n");
		err = -ENOMEM;
		goto err_cache;
	}

	err = create_debugfs_files(dev);
	if (err) {
		err = -ENOMEM;
		goto err_wq;
	}

	return 0;

err_wq:
	destroy_workqueue(cmd->wq);

err_cache:
	destroy_msg_cache(dev);

err_free_page:
	free_cmd_page(dev, cmd);

err_free_pool:
	dma_pool_destroy(cmd->pool);

	return err;
}