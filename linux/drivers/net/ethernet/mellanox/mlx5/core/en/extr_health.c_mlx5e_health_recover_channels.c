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
struct mlx5e_priv {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int mlx5e_safe_reopen_channels (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx5e_health_recover_channels(struct mlx5e_priv *priv)
{
	int err = 0;

	rtnl_lock();
	mutex_lock(&priv->state_lock);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		goto out;

	err = mlx5e_safe_reopen_channels(priv);

out:
	mutex_unlock(&priv->state_lock);
	rtnl_unlock();

	return err;
}