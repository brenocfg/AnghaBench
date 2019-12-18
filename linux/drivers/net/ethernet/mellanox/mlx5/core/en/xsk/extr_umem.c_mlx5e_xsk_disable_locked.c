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
typedef  size_t u16 ;
struct xdp_umem {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xdp_prog; } ;
struct TYPE_3__ {struct mlx5e_channel** c; TYPE_2__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  xsk; TYPE_1__ channels; int /*<<< orphan*/  state; } ;
struct mlx5e_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_close_xsk (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_deactivate_xsk (struct mlx5e_channel*) ; 
 struct xdp_umem* mlx5e_xsk_get_umem (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mlx5e_xsk_redirect_rqt_to_drop (struct mlx5e_priv*,size_t) ; 
 int /*<<< orphan*/  mlx5e_xsk_remove_umem (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mlx5e_xsk_unmap_umem (struct mlx5e_priv*,struct xdp_umem*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_xsk_disable_locked(struct mlx5e_priv *priv, u16 ix)
{
	struct xdp_umem *umem = mlx5e_xsk_get_umem(&priv->channels.params,
						   &priv->xsk, ix);
	struct mlx5e_channel *c;

	if (unlikely(!umem))
		return -EINVAL;

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		goto remove_umem;

	/* XSK RQ and SQ are only created if XDP program is set. */
	if (!priv->channels.params.xdp_prog)
		goto remove_umem;

	c = priv->channels.c[ix];
	mlx5e_xsk_redirect_rqt_to_drop(priv, ix);
	mlx5e_deactivate_xsk(c);
	mlx5e_close_xsk(c);

remove_umem:
	mlx5e_xsk_remove_umem(&priv->xsk, ix);
	mlx5e_xsk_unmap_umem(priv, umem);

	return 0;
}