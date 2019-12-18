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
struct mlx5e_cq_param {int cq_period_mode; int /*<<< orphan*/  cqc; int /*<<< orphan*/  eq_ix; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma; } ;
struct TYPE_10__ {int npages; int page_shift; } ;
struct TYPE_9__ {TYPE_3__ db; TYPE_5__ buf; } ;
struct mlx5_core_cq {int dummy; } ;
struct mlx5e_cq {TYPE_4__ wq_ctrl; struct mlx5_core_cq mcq; struct mlx5_core_dev* mdev; } ;
struct TYPE_7__ {TYPE_1__* uar; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_6__ {int index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ADAPTER_PAGE_SHIFT ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_eqn ; 
 int /*<<< orphan*/  cq_context ; 
 int /*<<< orphan*/  cq_period_mode ; 
 int /*<<< orphan*/  create_cq_in ; 
 int /*<<< orphan*/  create_cq_out ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_create_cq (struct mlx5_core_dev*,struct mlx5_core_cq*,void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_fill_page_frag_array (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int mlx5_vector2eqn (struct mlx5_core_dev*,int /*<<< orphan*/ ,int*,unsigned int*) ; 
 int /*<<< orphan*/  mlx5e_cq_arm (struct mlx5e_cq*) ; 
 int /*<<< orphan*/  pas ; 
 int /*<<< orphan*/  uar_page ; 

__attribute__((used)) static int mlx5e_create_cq(struct mlx5e_cq *cq, struct mlx5e_cq_param *param)
{
	u32 out[MLX5_ST_SZ_DW(create_cq_out)];
	struct mlx5_core_dev *mdev = cq->mdev;
	struct mlx5_core_cq *mcq = &cq->mcq;

	void *in;
	void *cqc;
	int inlen;
	unsigned int irqn_not_used;
	int eqn;
	int err;

	err = mlx5_vector2eqn(mdev, param->eq_ix, &eqn, &irqn_not_used);
	if (err)
		return err;

	inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		sizeof(u64) * cq->wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);

	memcpy(cqc, param->cqc, sizeof(param->cqc));

	mlx5_fill_page_frag_array(&cq->wq_ctrl.buf,
				  (__be64 *)MLX5_ADDR_OF(create_cq_in, in, pas));

	MLX5_SET(cqc,   cqc, cq_period_mode, param->cq_period_mode);
	MLX5_SET(cqc,   cqc, c_eqn,         eqn);
	MLX5_SET(cqc,   cqc, uar_page,      mdev->priv.uar->index);
	MLX5_SET(cqc,   cqc, log_page_size, cq->wq_ctrl.buf.page_shift -
					    MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(cqc, cqc, dbr_addr,      cq->wq_ctrl.db.dma);

	err = mlx5_core_create_cq(mdev, mcq, in, inlen, out, sizeof(out));

	kvfree(in);

	if (err)
		return err;

	mlx5e_cq_arm(cq);

	return 0;
}