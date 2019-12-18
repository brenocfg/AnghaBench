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
struct xdp_umem {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int mlx5e_xsk_enable_locked (struct mlx5e_priv*,struct xdp_umem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_xsk_enable_umem(struct mlx5e_priv *priv, struct xdp_umem *umem,
				 u16 ix)
{
	int err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_xsk_enable_locked(priv, umem, ix);
	mutex_unlock(&priv->state_lock);

	return err;
}