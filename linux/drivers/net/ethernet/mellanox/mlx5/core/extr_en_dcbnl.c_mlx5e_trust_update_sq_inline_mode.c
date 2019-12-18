#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tx_min_inline_mode; } ;
struct TYPE_3__ {TYPE_2__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_1__ channels; int /*<<< orphan*/  state; } ;
struct mlx5e_channels {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_safe_switch_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_trust_update_tx_min_inline_mode (struct mlx5e_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_trust_update_sq_inline_mode(struct mlx5e_priv *priv)
{
	struct mlx5e_channels new_channels = {};

	mutex_lock(&priv->state_lock);

	new_channels.params = priv->channels.params;
	mlx5e_trust_update_tx_min_inline_mode(priv, &new_channels.params);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state)) {
		priv->channels.params = new_channels.params;
		goto out;
	}

	/* Skip if tx_min_inline is the same */
	if (new_channels.params.tx_min_inline_mode ==
	    priv->channels.params.tx_min_inline_mode)
		goto out;

	mlx5e_safe_switch_channels(priv, &new_channels, NULL);

out:
	mutex_unlock(&priv->state_lock);
}