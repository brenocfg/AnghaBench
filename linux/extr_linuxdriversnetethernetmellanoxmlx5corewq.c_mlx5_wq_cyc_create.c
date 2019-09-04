#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wq_param {int /*<<< orphan*/  buf_numa_node; int /*<<< orphan*/  db_numa_node; } ;
struct mlx5_frag_buf_ctrl {int /*<<< orphan*/  frag_buf; scalar_t__ sz_m1; } ;
struct mlx5_wq_cyc {int /*<<< orphan*/  db; struct mlx5_frag_buf_ctrl fbc; scalar_t__ sz; } ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
struct mlx5_wq_ctrl {TYPE_1__ db; struct mlx5_core_dev* mdev; int /*<<< orphan*/  buf; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (struct mlx5_wq_cyc*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_wq_stride ; 
 int /*<<< orphan*/  log_wq_sz ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_db_alloc_node (struct mlx5_core_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (struct mlx5_core_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_fill_fbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_frag_buf_ctrl*) ; 
 int mlx5_frag_buf_alloc_node (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_get_byte_size (struct mlx5_wq_cyc*) ; 

int mlx5_wq_cyc_create(struct mlx5_core_dev *mdev, struct mlx5_wq_param *param,
		       void *wqc, struct mlx5_wq_cyc *wq,
		       struct mlx5_wq_ctrl *wq_ctrl)
{
	struct mlx5_frag_buf_ctrl *fbc = &wq->fbc;
	int err;

	mlx5_fill_fbc(MLX5_GET(wq, wqc, log_wq_stride),
		      MLX5_GET(wq, wqc, log_wq_sz),
		      fbc);
	wq->sz    = wq->fbc.sz_m1 + 1;

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		return err;
	}

	err = mlx5_frag_buf_alloc_node(mdev, mlx5_wq_cyc_get_byte_size(wq),
				       &wq_ctrl->buf, param->buf_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n", err);
		goto err_db_free;
	}

	fbc->frag_buf = wq_ctrl->buf;
	wq->db  = wq_ctrl->db.db;

	wq_ctrl->mdev = mdev;

	return 0;

err_db_free:
	mlx5_db_free(mdev, &wq_ctrl->db);

	return err;
}