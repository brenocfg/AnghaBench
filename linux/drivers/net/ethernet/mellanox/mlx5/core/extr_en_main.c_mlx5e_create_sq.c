#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_sq_param {int /*<<< orphan*/  sqc; } ;
struct mlx5e_create_sq_param {int tis_lst_sz; int tisn; int cqn; int min_inline_mode; TYPE_4__* wq_ctrl; } ;
struct TYPE_6__ {int index; } ;
struct TYPE_7__ {TYPE_1__ bfreg; } ;
struct mlx5_core_dev {TYPE_2__ mlx5e_res; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_10__ {int npages; int page_shift; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma; } ;
struct TYPE_9__ {TYPE_5__ buf; TYPE_3__ db; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ADAPTER_PAGE_SHIFT ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 scalar_t__ MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_INLINE_MODE_VPORT_CONTEXT ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_SQC_STATE_RST ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_WQ_TYPE_CYCLIC ; 
 int /*<<< orphan*/  cqn ; 
 void* create_sq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  flush_in_error_en ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_wq_pg_sz ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_wqe_inline_mode ; 
 int mlx5_core_create_sq (struct mlx5_core_dev*,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fill_page_frag_array (TYPE_5__*,int /*<<< orphan*/ *) ; 
 void* pas ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  tis_lst_sz ; 
 int /*<<< orphan*/  tis_num_0 ; 
 int /*<<< orphan*/  uar_page ; 
 int /*<<< orphan*/  wq_type ; 
 int /*<<< orphan*/  wqe_inline_mode ; 

__attribute__((used)) static int mlx5e_create_sq(struct mlx5_core_dev *mdev,
			   struct mlx5e_sq_param *param,
			   struct mlx5e_create_sq_param *csp,
			   u32 *sqn)
{
	void *in;
	void *sqc;
	void *wq;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(create_sq_in) +
		sizeof(u64) * csp->wq_ctrl->buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
	wq = MLX5_ADDR_OF(sqc, sqc, wq);

	memcpy(sqc, param->sqc, sizeof(param->sqc));
	MLX5_SET(sqc,  sqc, tis_lst_sz, csp->tis_lst_sz);
	MLX5_SET(sqc,  sqc, tis_num_0, csp->tisn);
	MLX5_SET(sqc,  sqc, cqn, csp->cqn);

	if (MLX5_CAP_ETH(mdev, wqe_inline_mode) == MLX5_CAP_INLINE_MODE_VPORT_CONTEXT)
		MLX5_SET(sqc,  sqc, min_wqe_inline_mode, csp->min_inline_mode);

	MLX5_SET(sqc,  sqc, state, MLX5_SQC_STATE_RST);
	MLX5_SET(sqc,  sqc, flush_in_error_en, 1);

	MLX5_SET(wq,   wq, wq_type,       MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq,   wq, uar_page,      mdev->mlx5e_res.bfreg.index);
	MLX5_SET(wq,   wq, log_wq_pg_sz,  csp->wq_ctrl->buf.page_shift -
					  MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(wq, wq, dbr_addr,      csp->wq_ctrl->db.dma);

	mlx5_fill_page_frag_array(&csp->wq_ctrl->buf,
				  (__be64 *)MLX5_ADDR_OF(wq, wq, pas));

	err = mlx5_core_create_sq(mdev, in, inlen, sqn);

	kvfree(in);

	return err;
}