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
struct mlx5e_params {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int /*<<< orphan*/  MLX5E_SET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5e_init_rq_type_params (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  mlx5e_rx_is_linear_skb (struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 scalar_t__ mlx5e_rx_mpwqe_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_set_rq_type (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 scalar_t__ mlx5e_striding_rq_possible (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  slow_pci_heuristic (struct mlx5_core_dev*) ; 

void mlx5e_build_rq_params(struct mlx5_core_dev *mdev,
			   struct mlx5e_params *params)
{
	/* Prefer Striding RQ, unless any of the following holds:
	 * - Striding RQ configuration is not possible/supported.
	 * - Slow PCI heuristic.
	 * - Legacy RQ would use linear SKB while Striding RQ would use non-linear.
	 *
	 * No XSK params: checking the availability of striding RQ in general.
	 */
	if (!slow_pci_heuristic(mdev) &&
	    mlx5e_striding_rq_possible(mdev, params) &&
	    (mlx5e_rx_mpwqe_is_linear_skb(mdev, params, NULL) ||
	     !mlx5e_rx_is_linear_skb(params, NULL)))
		MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ, true);
	mlx5e_set_rq_type(mdev, params);
	mlx5e_init_rq_type_params(mdev, params);
}