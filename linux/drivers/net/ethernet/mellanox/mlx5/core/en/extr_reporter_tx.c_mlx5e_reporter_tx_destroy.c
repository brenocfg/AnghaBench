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
struct mlx5e_priv {int /*<<< orphan*/  tx_reporter; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_health_reporter_destroy (int /*<<< orphan*/ ) ; 

void mlx5e_reporter_tx_destroy(struct mlx5e_priv *priv)
{
	if (!priv->tx_reporter)
		return;

	devlink_health_reporter_destroy(priv->tx_reporter);
}