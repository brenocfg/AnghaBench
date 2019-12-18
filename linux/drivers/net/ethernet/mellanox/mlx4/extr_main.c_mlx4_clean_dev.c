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
struct TYPE_2__ {unsigned long flags; struct mlx4_dev_persistent* persist; } ;
struct mlx4_priv {TYPE_1__ dev; } ;
struct mlx4_dev_persistent {int dummy; } ;
struct mlx4_dev {unsigned long flags; struct mlx4_dev_persistent* persist; } ;

/* Variables and functions */
 unsigned long RESET_PERSIST_MASK_FLAGS ; 
 int /*<<< orphan*/  memset (struct mlx4_priv*,int /*<<< orphan*/ ,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

__attribute__((used)) static void mlx4_clean_dev(struct mlx4_dev *dev)
{
	struct mlx4_dev_persistent *persist = dev->persist;
	struct mlx4_priv *priv = mlx4_priv(dev);
	unsigned long	flags = (dev->flags & RESET_PERSIST_MASK_FLAGS);

	memset(priv, 0, sizeof(*priv));
	priv->dev.persist = persist;
	priv->dev.flags = flags;
}