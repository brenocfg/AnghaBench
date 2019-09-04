#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  fbc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  fbc; } ;
struct mlx5_wq_qp {TYPE_1__ sq; TYPE_2__ rq; } ;
struct mlx5_wq_param {int /*<<< orphan*/  buf_numa_node; int /*<<< orphan*/  db_numa_node; } ;
struct TYPE_7__ {int /*<<< orphan*/ * db; } ;
struct mlx5_wq_ctrl {TYPE_3__ db; struct mlx5_core_dev* mdev; int /*<<< orphan*/  buf; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 size_t MLX5_RCV_DBR ; 
 int MLX5_SEND_WQE_BB ; 
 size_t MLX5_SND_DBR ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  log_rq_size ; 
 int /*<<< orphan*/  log_rq_stride ; 
 int /*<<< orphan*/  log_sq_size ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_db_alloc_node (struct mlx5_core_dev*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (struct mlx5_core_dev*,TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5_fill_fbc (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fill_fbc_offset (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int mlx5_frag_buf_alloc_node (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_qp_set_frag_buf (int /*<<< orphan*/ *,struct mlx5_wq_qp*) ; 
 int mlx5_wq_cyc_get_byte_size (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_wq_qp_get_byte_size (struct mlx5_wq_qp*) ; 

int mlx5_wq_qp_create(struct mlx5_core_dev *mdev, struct mlx5_wq_param *param,
		      void *qpc, struct mlx5_wq_qp *wq,
		      struct mlx5_wq_ctrl *wq_ctrl)
{
	u16 sq_strides_offset;
	u32 rq_pg_remainder;
	int err;

	mlx5_fill_fbc(MLX5_GET(qpc, qpc, log_rq_stride) + 4,
		      MLX5_GET(qpc, qpc, log_rq_size),
		      &wq->rq.fbc);

	rq_pg_remainder   = mlx5_wq_cyc_get_byte_size(&wq->rq) % PAGE_SIZE;
	sq_strides_offset = rq_pg_remainder / MLX5_SEND_WQE_BB;

	mlx5_fill_fbc_offset(ilog2(MLX5_SEND_WQE_BB),
			     MLX5_GET(qpc, qpc, log_sq_size),
			     sq_strides_offset,
			     &wq->sq.fbc);

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		return err;
	}

	err = mlx5_frag_buf_alloc_node(mdev, mlx5_wq_qp_get_byte_size(wq),
				       &wq_ctrl->buf, param->buf_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n", err);
		goto err_db_free;
	}

	mlx5_qp_set_frag_buf(&wq_ctrl->buf, wq);

	wq->rq.db  = &wq_ctrl->db.db[MLX5_RCV_DBR];
	wq->sq.db  = &wq_ctrl->db.db[MLX5_SND_DBR];

	wq_ctrl->mdev = mdev;

	return 0;

err_db_free:
	mlx5_db_free(mdev, &wq_ctrl->db);

	return err;
}