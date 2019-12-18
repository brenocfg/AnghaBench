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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  rqn; } ;
struct mlx5e_priv {TYPE_1__ drop_rq; } ;

/* Variables and functions */
 int mlx5e_redirect_xsk_rqt (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5e_xsk_redirect_rqt_to_drop(struct mlx5e_priv *priv, u16 ix)
{
	return mlx5e_redirect_xsk_rqt(priv, ix, priv->drop_rq.rqn);
}