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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int mlx5e_xsk_disable_locked (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_xsk_disable_umem(struct mlx5e_priv *priv, u16 ix)
{
	int err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_xsk_disable_locked(priv, ix);
	mutex_unlock(&priv->state_lock);

	return err;
}