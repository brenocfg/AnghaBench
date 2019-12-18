#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  db_numa_node; } ;
struct mlx5e_sq_param {TYPE_3__ wq; int /*<<< orphan*/  sqc; } ;
struct mlx5_wq_cyc {int /*<<< orphan*/ * db; } ;
struct mlx5e_icosq {int /*<<< orphan*/  wq_ctrl; int /*<<< orphan*/  recover_work; int /*<<< orphan*/  uar_map; struct mlx5e_channel* channel; struct mlx5_wq_cyc wq; } ;
struct mlx5e_channel {int /*<<< orphan*/  cpu; struct mlx5_core_dev* mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
struct TYPE_5__ {TYPE_1__ bfreg; } ;
struct mlx5_core_dev {TYPE_2__ mlx5e_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MLX5_SND_DBR ; 
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 int mlx5_wq_cyc_create (struct mlx5_core_dev*,TYPE_3__*,void*,struct mlx5_wq_cyc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int mlx5e_alloc_icosq_db (struct mlx5e_icosq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_icosq_err_cqe_work ; 
 int /*<<< orphan*/  sqc ; 
 struct mlx5_wq_cyc* wq ; 

__attribute__((used)) static int mlx5e_alloc_icosq(struct mlx5e_channel *c,
			     struct mlx5e_sq_param *param,
			     struct mlx5e_icosq *sq)
{
	void *sqc_wq               = MLX5_ADDR_OF(sqc, param->sqc, wq);
	struct mlx5_core_dev *mdev = c->mdev;
	struct mlx5_wq_cyc *wq = &sq->wq;
	int err;

	sq->channel   = c;
	sq->uar_map   = mdev->mlx5e_res.bfreg.map;

	param->wq.db_numa_node = cpu_to_node(c->cpu);
	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, wq, &sq->wq_ctrl);
	if (err)
		return err;
	wq->db = &wq->db[MLX5_SND_DBR];

	err = mlx5e_alloc_icosq_db(sq, cpu_to_node(c->cpu));
	if (err)
		goto err_sq_wq_destroy;

	INIT_WORK(&sq->recover_work, mlx5e_icosq_err_cqe_work);

	return 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

	return err;
}