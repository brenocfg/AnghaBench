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
struct TYPE_3__ {int /*<<< orphan*/  refcnt; } ;
struct mlx5e_priv {TYPE_1__ xsk; } ;
struct mlx5e_channels {int num; TYPE_2__** c; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CHANNEL_STATE_XSK ; 
 int /*<<< orphan*/  mlx5e_xsk_redirect_rqt_to_drop (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5e_xsk_redirect_rqts_to_drop(struct mlx5e_priv *priv, struct mlx5e_channels *chs)
{
	int i;

	if (!priv->xsk.refcnt)
		return;

	for (i = 0; i < chs->num; i++) {
		if (!test_bit(MLX5E_CHANNEL_STATE_XSK, chs->c[i]->state))
			continue;

		mlx5e_xsk_redirect_rqt_to_drop(priv, i);
	}
}