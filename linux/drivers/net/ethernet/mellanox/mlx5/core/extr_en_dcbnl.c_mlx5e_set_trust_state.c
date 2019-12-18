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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  trust_state; } ;
struct mlx5e_priv {TYPE_1__ dcbx_dp; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_set_trust_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_trust_update_sq_inline_mode (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5e_set_trust_state(struct mlx5e_priv *priv, u8 trust_state)
{
	int err;

	err = mlx5_set_trust_state(priv->mdev, trust_state);
	if (err)
		return err;
	priv->dcbx_dp.trust_state = trust_state;
	mlx5e_trust_update_sq_inline_mode(priv);

	return err;
}