#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int initialized; int toggle; scalar_t__ pool; scalar_t__ hcr; scalar_t__ use_events; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  slave_cmd_mutex; int /*<<< orphan*/  switch_sem; } ;
struct TYPE_5__ {scalar_t__ vhcr; int /*<<< orphan*/  vhcr_dma; } ;
struct mlx4_priv {TYPE_3__ cmd; TYPE_1__ mfunc; } ;
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_4__* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX4_CMD_CLEANUP_HCR ; 
 int MLX4_CMD_CLEANUP_POOL ; 
 int MLX4_CMD_CLEANUP_STRUCT ; 
 int MLX4_CMD_CLEANUP_VHCR ; 
 scalar_t__ MLX4_HCR_BASE ; 
 int /*<<< orphan*/  MLX4_HCR_SIZE ; 
 int /*<<< orphan*/  MLX4_MAILBOX_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 scalar_t__ ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cmd_cleanup (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_resource_start (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

int mlx4_cmd_init(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int flags = 0;

	if (!priv->cmd.initialized) {
		init_rwsem(&priv->cmd.switch_sem);
		mutex_init(&priv->cmd.slave_cmd_mutex);
		sema_init(&priv->cmd.poll_sem, 1);
		priv->cmd.use_events = 0;
		priv->cmd.toggle     = 1;
		priv->cmd.initialized = 1;
		flags |= MLX4_CMD_CLEANUP_STRUCT;
	}

	if (!mlx4_is_slave(dev) && !priv->cmd.hcr) {
		priv->cmd.hcr = ioremap(pci_resource_start(dev->persist->pdev,
					0) + MLX4_HCR_BASE, MLX4_HCR_SIZE);
		if (!priv->cmd.hcr) {
			mlx4_err(dev, "Couldn't map command register\n");
			goto err;
		}
		flags |= MLX4_CMD_CLEANUP_HCR;
	}

	if (mlx4_is_mfunc(dev) && !priv->mfunc.vhcr) {
		priv->mfunc.vhcr = dma_alloc_coherent(&dev->persist->pdev->dev,
						      PAGE_SIZE,
						      &priv->mfunc.vhcr_dma,
						      GFP_KERNEL);
		if (!priv->mfunc.vhcr)
			goto err;

		flags |= MLX4_CMD_CLEANUP_VHCR;
	}

	if (!priv->cmd.pool) {
		priv->cmd.pool = dma_pool_create("mlx4_cmd",
						 &dev->persist->pdev->dev,
						 MLX4_MAILBOX_SIZE,
						 MLX4_MAILBOX_SIZE, 0);
		if (!priv->cmd.pool)
			goto err;

		flags |= MLX4_CMD_CLEANUP_POOL;
	}

	return 0;

err:
	mlx4_cmd_cleanup(dev, flags);
	return -ENOMEM;
}