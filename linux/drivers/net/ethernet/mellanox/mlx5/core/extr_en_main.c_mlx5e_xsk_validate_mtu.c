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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct xdp_umem {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_xsk_param {scalar_t__ chunk_size; } ;
struct mlx5e_params {int /*<<< orphan*/  sw_mtu; } ;
struct TYPE_2__ {scalar_t__ num_channels; int /*<<< orphan*/  xsk; } ;
struct mlx5e_channels {TYPE_1__ params; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5E_HW2SW_MTU (struct mlx5e_params*,scalar_t__) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mlx5e_build_xsk_param (struct xdp_umem*,struct mlx5e_xsk_param*) ; 
 scalar_t__ mlx5e_get_linear_rq_headroom (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 
 int /*<<< orphan*/  mlx5e_validate_xsk_param (struct mlx5e_params*,struct mlx5e_xsk_param*,struct mlx5_core_dev*) ; 
 int mlx5e_xdp_max_mtu (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 
 struct xdp_umem* mlx5e_xsk_get_umem (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static bool mlx5e_xsk_validate_mtu(struct net_device *netdev,
				   struct mlx5e_channels *chs,
				   struct mlx5e_params *new_params,
				   struct mlx5_core_dev *mdev)
{
	u16 ix;

	for (ix = 0; ix < chs->params.num_channels; ix++) {
		struct xdp_umem *umem = mlx5e_xsk_get_umem(&chs->params, chs->params.xsk, ix);
		struct mlx5e_xsk_param xsk;

		if (!umem)
			continue;

		mlx5e_build_xsk_param(umem, &xsk);

		if (!mlx5e_validate_xsk_param(new_params, &xsk, mdev)) {
			u32 hr = mlx5e_get_linear_rq_headroom(new_params, &xsk);
			int max_mtu_frame, max_mtu_page, max_mtu;

			/* Two criteria must be met:
			 * 1. HW MTU + all headrooms <= XSK frame size.
			 * 2. Size of SKBs allocated on XDP_PASS <= PAGE_SIZE.
			 */
			max_mtu_frame = MLX5E_HW2SW_MTU(new_params, xsk.chunk_size - hr);
			max_mtu_page = mlx5e_xdp_max_mtu(new_params, &xsk);
			max_mtu = min(max_mtu_frame, max_mtu_page);

			netdev_err(netdev, "MTU %d is too big for an XSK running on channel %hu. Try MTU <= %d\n",
				   new_params->sw_mtu, ix, max_mtu);
			return false;
		}
	}

	return true;
}