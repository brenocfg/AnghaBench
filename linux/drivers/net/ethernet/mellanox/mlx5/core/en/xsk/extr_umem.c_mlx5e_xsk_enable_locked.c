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
typedef  size_t u16 ;
struct xdp_umem {int dummy; } ;
struct mlx5e_xsk_param {int dummy; } ;
struct mlx5e_params {int /*<<< orphan*/  xdp_prog; } ;
struct TYPE_2__ {struct mlx5e_channel** c; struct mlx5e_params params; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; int /*<<< orphan*/  xsk; TYPE_1__ channels; int /*<<< orphan*/  state; } ;
struct mlx5e_channel {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_activate_xsk (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_build_xsk_param (struct xdp_umem*,struct mlx5e_xsk_param*) ; 
 int /*<<< orphan*/  mlx5e_close_xsk (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_deactivate_xsk (struct mlx5e_channel*) ; 
 int mlx5e_open_xsk (struct mlx5e_priv*,struct mlx5e_params*,struct mlx5e_xsk_param*,struct xdp_umem*,struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_validate_xsk_param (struct mlx5e_params*,struct mlx5e_xsk_param*,int /*<<< orphan*/ ) ; 
 int mlx5e_xsk_add_umem (int /*<<< orphan*/ *,struct xdp_umem*,size_t) ; 
 int mlx5e_xsk_get_umem (struct mlx5e_params*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mlx5e_xsk_is_umem_sane (struct xdp_umem*) ; 
 int mlx5e_xsk_map_umem (struct mlx5e_priv*,struct xdp_umem*) ; 
 int mlx5e_xsk_redirect_rqt_to_channel (struct mlx5e_priv*,struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_xsk_remove_umem (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mlx5e_xsk_unmap_umem (struct mlx5e_priv*,struct xdp_umem*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_xsk_enable_locked(struct mlx5e_priv *priv,
				   struct xdp_umem *umem, u16 ix)
{
	struct mlx5e_params *params = &priv->channels.params;
	struct mlx5e_xsk_param xsk;
	struct mlx5e_channel *c;
	int err;

	if (unlikely(mlx5e_xsk_get_umem(&priv->channels.params, &priv->xsk, ix)))
		return -EBUSY;

	if (unlikely(!mlx5e_xsk_is_umem_sane(umem)))
		return -EINVAL;

	err = mlx5e_xsk_map_umem(priv, umem);
	if (unlikely(err))
		return err;

	err = mlx5e_xsk_add_umem(&priv->xsk, umem, ix);
	if (unlikely(err))
		goto err_unmap_umem;

	mlx5e_build_xsk_param(umem, &xsk);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state)) {
		/* XSK objects will be created on open. */
		goto validate_closed;
	}

	if (!params->xdp_prog) {
		/* XSK objects will be created when an XDP program is set,
		 * and the channels are reopened.
		 */
		goto validate_closed;
	}

	c = priv->channels.c[ix];

	err = mlx5e_open_xsk(priv, params, &xsk, umem, c);
	if (unlikely(err))
		goto err_remove_umem;

	mlx5e_activate_xsk(c);

	/* Don't wait for WQEs, because the newer xdpsock sample doesn't provide
	 * any Fill Ring entries at the setup stage.
	 */

	err = mlx5e_xsk_redirect_rqt_to_channel(priv, priv->channels.c[ix]);
	if (unlikely(err))
		goto err_deactivate;

	return 0;

err_deactivate:
	mlx5e_deactivate_xsk(c);
	mlx5e_close_xsk(c);

err_remove_umem:
	mlx5e_xsk_remove_umem(&priv->xsk, ix);

err_unmap_umem:
	mlx5e_xsk_unmap_umem(priv, umem);

	return err;

validate_closed:
	/* Check the configuration in advance, rather than fail at a later stage
	 * (in mlx5e_xdp_set or on open) and end up with no channels.
	 */
	if (!mlx5e_validate_xsk_param(params, &xsk, priv->mdev)) {
		err = -EINVAL;
		goto err_remove_umem;
	}

	return 0;
}