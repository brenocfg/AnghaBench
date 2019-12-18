#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_dev {TYPE_5__* mdev; } ;
struct TYPE_17__ {scalar_t__ db; } ;
struct TYPE_15__ {int npages; scalar_t__ page_shift; } ;
struct TYPE_18__ {TYPE_4__ frag_buf; } ;
struct TYPE_12__ {int cqe_sz; scalar_t__ arm_db; scalar_t__ set_ci_db; } ;
struct mlx5_ib_cq {TYPE_6__ db; TYPE_9__ buf; TYPE_1__ mcq; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_14__ {TYPE_2__* uar; } ;
struct TYPE_16__ {TYPE_3__ priv; } ;
struct TYPE_13__ {int index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX5_ADAPTER_PAGE_SHIFT ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int alloc_cq_frag_buf (struct mlx5_ib_dev*,TYPE_9__*,int,int) ; 
 int /*<<< orphan*/ * cq_context ; 
 int /*<<< orphan*/  create_cq_in ; 
 int /*<<< orphan*/  free_cq_buf (struct mlx5_ib_dev*,TYPE_9__*) ; 
 int /*<<< orphan*/  init_cq_frag_buf (struct mlx5_ib_cq*,TYPE_9__*) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_page_size ; 
 int mlx5_db_alloc (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mlx5_db_free (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mlx5_fill_page_frag_array (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_cq_kernel(struct mlx5_ib_dev *dev, struct mlx5_ib_cq *cq,
			    int entries, int cqe_size,
			    u32 **cqb, int *index, int *inlen)
{
	__be64 *pas;
	void *cqc;
	int err;

	err = mlx5_db_alloc(dev->mdev, &cq->db);
	if (err)
		return err;

	cq->mcq.set_ci_db  = cq->db.db;
	cq->mcq.arm_db     = cq->db.db + 1;
	cq->mcq.cqe_sz = cqe_size;

	err = alloc_cq_frag_buf(dev, &cq->buf, entries, cqe_size);
	if (err)
		goto err_db;

	init_cq_frag_buf(cq, &cq->buf);

	*inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		 MLX5_FLD_SZ_BYTES(create_cq_in, pas[0]) *
		 cq->buf.frag_buf.npages;
	*cqb = kvzalloc(*inlen, GFP_KERNEL);
	if (!*cqb) {
		err = -ENOMEM;
		goto err_buf;
	}

	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, *cqb, pas);
	mlx5_fill_page_frag_array(&cq->buf.frag_buf, pas);

	cqc = MLX5_ADDR_OF(create_cq_in, *cqb, cq_context);
	MLX5_SET(cqc, cqc, log_page_size,
		 cq->buf.frag_buf.page_shift -
		 MLX5_ADAPTER_PAGE_SHIFT);

	*index = dev->mdev->priv.uar->index;

	return 0;

err_buf:
	free_cq_buf(dev, &cq->buf);

err_db:
	mlx5_db_free(dev->mdev, &cq->db);
	return err;
}