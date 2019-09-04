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
struct mlx5_priv {int /*<<< orphan*/  irq_info; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; struct mlx5_priv priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_free_irq_vectors(struct mlx5_core_dev *dev)
{
	struct mlx5_priv *priv = &dev->priv;

	pci_free_irq_vectors(dev->pdev);
	kfree(priv->irq_info);
}