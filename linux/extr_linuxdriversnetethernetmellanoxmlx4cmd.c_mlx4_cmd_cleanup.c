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
struct TYPE_8__ {scalar_t__ initialized; int /*<<< orphan*/ * hcr; int /*<<< orphan*/ * pool; } ;
struct TYPE_7__ {int /*<<< orphan*/ * vhcr; int /*<<< orphan*/  vhcr_dma; } ;
struct mlx4_priv {TYPE_4__ cmd; TYPE_3__ mfunc; } ;
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MLX4_CMD_CLEANUP_HCR ; 
 int MLX4_CMD_CLEANUP_POOL ; 
 int MLX4_CMD_CLEANUP_STRUCT ; 
 int MLX4_CMD_CLEANUP_VHCR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_cmd_cleanup(struct mlx4_dev *dev, int cleanup_mask)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (priv->cmd.pool && (cleanup_mask & MLX4_CMD_CLEANUP_POOL)) {
		dma_pool_destroy(priv->cmd.pool);
		priv->cmd.pool = NULL;
	}

	if (!mlx4_is_slave(dev) && priv->cmd.hcr &&
	    (cleanup_mask & MLX4_CMD_CLEANUP_HCR)) {
		iounmap(priv->cmd.hcr);
		priv->cmd.hcr = NULL;
	}
	if (mlx4_is_mfunc(dev) && priv->mfunc.vhcr &&
	    (cleanup_mask & MLX4_CMD_CLEANUP_VHCR)) {
		dma_free_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
				  priv->mfunc.vhcr, priv->mfunc.vhcr_dma);
		priv->mfunc.vhcr = NULL;
	}
	if (priv->cmd.initialized && (cleanup_mask & MLX4_CMD_CLEANUP_STRUCT))
		priv->cmd.initialized = 0;
}