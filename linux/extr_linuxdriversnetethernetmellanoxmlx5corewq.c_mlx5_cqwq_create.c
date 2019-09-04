#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wq_param {int /*<<< orphan*/  buf_numa_node; int /*<<< orphan*/  db_numa_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
struct mlx5_wq_ctrl {TYPE_1__ db; struct mlx5_core_dev* mdev; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  frag_buf; } ;
struct mlx5_cqwq {int /*<<< orphan*/  db; TYPE_3__ fbc; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_init_cq_frag_buf (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_cqwq_get_byte_size (struct mlx5_cqwq*) ; 
 int mlx5_db_alloc_node (struct mlx5_core_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (struct mlx5_core_dev*,TYPE_1__*) ; 
 int mlx5_frag_buf_alloc_node (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mlx5_cqwq_create(struct mlx5_core_dev *mdev, struct mlx5_wq_param *param,
		     void *cqc, struct mlx5_cqwq *wq,
		     struct mlx5_wq_ctrl *wq_ctrl)
{
	int err;

	mlx5_core_init_cq_frag_buf(&wq->fbc, cqc);

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		return err;
	}

	err = mlx5_frag_buf_alloc_node(mdev, mlx5_cqwq_get_byte_size(wq),
				       &wq_ctrl->buf,
				       param->buf_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n",
			       err);
		goto err_db_free;
	}

	wq->fbc.frag_buf = wq_ctrl->buf;
	wq->db  = wq_ctrl->db.db;

	wq_ctrl->mdev = mdev;

	return 0;

err_db_free:
	mlx5_db_free(mdev, &wq_ctrl->db);

	return err;
}