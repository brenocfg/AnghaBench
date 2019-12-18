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
struct mlx5e_params {int /*<<< orphan*/  rq_wq_type; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5E_GET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int /*<<< orphan*/  MLX5_WQ_TYPE_CYCLIC ; 
 int /*<<< orphan*/  MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 scalar_t__ mlx5e_striding_rq_possible (struct mlx5_core_dev*,struct mlx5e_params*) ; 

void mlx5e_set_rq_type(struct mlx5_core_dev *mdev, struct mlx5e_params *params)
{
	params->rq_wq_type = mlx5e_striding_rq_possible(mdev, params) &&
		MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ) ?
		MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ :
		MLX5_WQ_TYPE_CYCLIC;
}