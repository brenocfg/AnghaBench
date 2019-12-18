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
struct mlx5e_rq_param {int dummy; } ;
struct mlx5e_cq {int dummy; } ;
struct mlx5e_rq {struct mlx5e_cq cq; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5e_cq_param {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RQC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_RQC_STATE_RST ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5e_alloc_drop_cq (struct mlx5_core_dev*,struct mlx5e_cq*,struct mlx5e_cq_param*) ; 
 int mlx5e_alloc_drop_rq (struct mlx5_core_dev*,struct mlx5e_rq*,struct mlx5e_rq_param*) ; 
 int /*<<< orphan*/  mlx5e_build_drop_rq_param (struct mlx5e_priv*,struct mlx5e_rq_param*) ; 
 int mlx5e_create_cq (struct mlx5e_cq*,struct mlx5e_cq_param*) ; 
 int mlx5e_create_rq (struct mlx5e_rq*,struct mlx5e_rq_param*) ; 
 int /*<<< orphan*/  mlx5e_destroy_cq (struct mlx5e_cq*) ; 
 int /*<<< orphan*/  mlx5e_free_cq (struct mlx5e_cq*) ; 
 int /*<<< orphan*/  mlx5e_free_rq (struct mlx5e_rq*) ; 
 int mlx5e_modify_rq_state (struct mlx5e_rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5e_open_drop_rq(struct mlx5e_priv *priv,
		       struct mlx5e_rq *drop_rq)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5e_cq_param cq_param = {};
	struct mlx5e_rq_param rq_param = {};
	struct mlx5e_cq *cq = &drop_rq->cq;
	int err;

	mlx5e_build_drop_rq_param(priv, &rq_param);

	err = mlx5e_alloc_drop_cq(mdev, cq, &cq_param);
	if (err)
		return err;

	err = mlx5e_create_cq(cq, &cq_param);
	if (err)
		goto err_free_cq;

	err = mlx5e_alloc_drop_rq(mdev, drop_rq, &rq_param);
	if (err)
		goto err_destroy_cq;

	err = mlx5e_create_rq(drop_rq, &rq_param);
	if (err)
		goto err_free_rq;

	err = mlx5e_modify_rq_state(drop_rq, MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY);
	if (err)
		mlx5_core_warn(priv->mdev, "modify_rq_state failed, rx_if_down_packets won't be counted %d\n", err);

	return 0;

err_free_rq:
	mlx5e_free_rq(drop_rq);

err_destroy_cq:
	mlx5e_destroy_cq(cq);

err_free_cq:
	mlx5e_free_cq(cq);

	return err;
}