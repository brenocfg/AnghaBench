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
struct mlx5e_priv {TYPE_1__* mdev; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_ASYNC_EVENTS_ENABLED ; 
 int /*<<< orphan*/  MLX5_EQ_VEC_ASYNC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_disable_async_events(struct mlx5e_priv *priv)
{
	clear_bit(MLX5E_STATE_ASYNC_EVENTS_ENABLED, &priv->state);
	synchronize_irq(pci_irq_vector(priv->mdev->pdev, MLX5_EQ_VEC_ASYNC));
}