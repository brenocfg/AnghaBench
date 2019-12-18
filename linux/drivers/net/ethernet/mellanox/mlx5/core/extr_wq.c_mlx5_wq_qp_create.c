#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  fbc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  fbc; } ;
struct mlx5_wq_qp {TYPE_2__ sq; TYPE_1__ rq; } ;
struct mlx5_wq_param {int /*<<< orphan*/  buf_numa_node; int /*<<< orphan*/  db_numa_node; } ;
struct TYPE_9__ {int /*<<< orphan*/ * db; } ;
struct TYPE_8__ {int frags; } ;
struct mlx5_wq_ctrl {TYPE_4__ db; struct mlx5_core_dev* mdev; TYPE_3__ buf; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 size_t MLX5_RCV_DBR ; 
 int MLX5_SEND_WQE_BB ; 
 size_t MLX5_SND_DBR ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ ilog2 (int) ; 
 int /*<<< orphan*/  log_rq_size ; 
 scalar_t__ log_rq_stride ; 
 int /*<<< orphan*/  log_sq_size ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_db_alloc_node (struct mlx5_core_dev*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (struct mlx5_core_dev*,TYPE_4__*) ; 
 int mlx5_frag_buf_alloc_node (struct mlx5_core_dev*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_init_fbc (int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_init_fbc_offset (int,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int wq_get_byte_sz (scalar_t__,scalar_t__) ; 

int mlx5_wq_qp_create(struct mlx5_core_dev *mdev, struct mlx5_wq_param *param,
		      void *qpc, struct mlx5_wq_qp *wq,
		      struct mlx5_wq_ctrl *wq_ctrl)
{
	u8 log_rq_stride = MLX5_GET(qpc, qpc, log_rq_stride) + 4;
	u8 log_rq_sz     = MLX5_GET(qpc, qpc, log_rq_size);
	u8 log_sq_stride = ilog2(MLX5_SEND_WQE_BB);
	u8 log_sq_sz     = MLX5_GET(qpc, qpc, log_sq_size);

	u32 rq_byte_size;
	int err;



	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		return err;
	}

	err = mlx5_frag_buf_alloc_node(mdev,
				       wq_get_byte_sz(log_rq_sz, log_rq_stride) +
				       wq_get_byte_sz(log_sq_sz, log_sq_stride),
				       &wq_ctrl->buf, param->buf_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n", err);
		goto err_db_free;
	}

	mlx5_init_fbc(wq_ctrl->buf.frags, log_rq_stride, log_rq_sz, &wq->rq.fbc);

	rq_byte_size = wq_get_byte_sz(log_rq_sz, log_rq_stride);

	if (rq_byte_size < PAGE_SIZE) {
		/* SQ starts within the same page of the RQ */
		u16 sq_strides_offset = rq_byte_size / MLX5_SEND_WQE_BB;

		mlx5_init_fbc_offset(wq_ctrl->buf.frags,
				     log_sq_stride, log_sq_sz, sq_strides_offset,
				     &wq->sq.fbc);
	} else {
		u16 rq_npages = rq_byte_size >> PAGE_SHIFT;

		mlx5_init_fbc(wq_ctrl->buf.frags + rq_npages,
			      log_sq_stride, log_sq_sz, &wq->sq.fbc);
	}

	wq->rq.db  = &wq_ctrl->db.db[MLX5_RCV_DBR];
	wq->sq.db  = &wq_ctrl->db.db[MLX5_SND_DBR];

	wq_ctrl->mdev = mdev;

	return 0;

err_db_free:
	mlx5_db_free(mdev, &wq_ctrl->db);

	return err;
}