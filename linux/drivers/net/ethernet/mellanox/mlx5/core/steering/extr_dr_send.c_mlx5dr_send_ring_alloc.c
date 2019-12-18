#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int max_send_wr; int /*<<< orphan*/  max_inline_size; } ;
struct mlx5dr_domain {TYPE_3__* send_ring; int /*<<< orphan*/  mdev; int /*<<< orphan*/  pdn; TYPE_2__ info; int /*<<< orphan*/  uar; } ;
struct dr_qp_init_attr {int max_send_wr; int /*<<< orphan*/  uar; int /*<<< orphan*/  pdn; int /*<<< orphan*/  cqn; } ;
struct TYPE_9__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_13__ {TYPE_5__* qp; TYPE_1__ mcq; } ;
struct TYPE_12__ {int /*<<< orphan*/  max_inline_data; } ;
struct TYPE_11__ {int signal_th; int max_post_send_size; int buf_size; TYPE_6__* cq; TYPE_5__* qp; struct TYPE_11__* buf; void* mr; void* sync_mr; struct TYPE_11__* sync_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_CHUNK_SIZE_1K ; 
 int /*<<< orphan*/  DR_ICM_TYPE_STE ; 
 int /*<<< orphan*/  DR_STE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MIN_READ_SYNC ; 
 int QUEUE_SIZE ; 
 int SIGNAL_PER_DIV_QUEUE ; 
 TYPE_6__* dr_create_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* dr_create_rc_qp (int /*<<< orphan*/ ,struct dr_qp_init_attr*) ; 
 int /*<<< orphan*/  dr_dereg_mr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dr_destroy_cq (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  dr_destroy_qp (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int dr_prepare_qp_to_rts (struct mlx5dr_domain*) ; 
 void* dr_reg_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5dr_icm_pool_chunk_size_to_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5dr_send_ring_alloc(struct mlx5dr_domain *dmn)
{
	struct dr_qp_init_attr init_attr = {};
	int cq_size;
	int size;
	int ret;

	dmn->send_ring = kzalloc(sizeof(*dmn->send_ring), GFP_KERNEL);
	if (!dmn->send_ring)
		return -ENOMEM;

	cq_size = QUEUE_SIZE + 1;
	dmn->send_ring->cq = dr_create_cq(dmn->mdev, dmn->uar, cq_size);
	if (!dmn->send_ring->cq) {
		ret = -ENOMEM;
		goto free_send_ring;
	}

	init_attr.cqn = dmn->send_ring->cq->mcq.cqn;
	init_attr.pdn = dmn->pdn;
	init_attr.uar = dmn->uar;
	init_attr.max_send_wr = QUEUE_SIZE;

	dmn->send_ring->qp = dr_create_rc_qp(dmn->mdev, &init_attr);
	if (!dmn->send_ring->qp)  {
		ret = -ENOMEM;
		goto clean_cq;
	}

	dmn->send_ring->cq->qp = dmn->send_ring->qp;

	dmn->info.max_send_wr = QUEUE_SIZE;
	dmn->info.max_inline_size = min(dmn->send_ring->qp->max_inline_data,
					DR_STE_SIZE);

	dmn->send_ring->signal_th = dmn->info.max_send_wr /
		SIGNAL_PER_DIV_QUEUE;

	/* Prepare qp to be used */
	ret = dr_prepare_qp_to_rts(dmn);
	if (ret)
		goto clean_qp;

	dmn->send_ring->max_post_send_size =
		mlx5dr_icm_pool_chunk_size_to_byte(DR_CHUNK_SIZE_1K,
						   DR_ICM_TYPE_STE);

	/* Allocating the max size as a buffer for writing */
	size = dmn->send_ring->signal_th * dmn->send_ring->max_post_send_size;
	dmn->send_ring->buf = kzalloc(size, GFP_KERNEL);
	if (!dmn->send_ring->buf) {
		ret = -ENOMEM;
		goto clean_qp;
	}

	dmn->send_ring->buf_size = size;

	dmn->send_ring->mr = dr_reg_mr(dmn->mdev,
				       dmn->pdn, dmn->send_ring->buf, size);
	if (!dmn->send_ring->mr) {
		ret = -ENOMEM;
		goto free_mem;
	}

	dmn->send_ring->sync_mr = dr_reg_mr(dmn->mdev,
					    dmn->pdn, dmn->send_ring->sync_buff,
					    MIN_READ_SYNC);
	if (!dmn->send_ring->sync_mr) {
		ret = -ENOMEM;
		goto clean_mr;
	}

	return 0;

clean_mr:
	dr_dereg_mr(dmn->mdev, dmn->send_ring->mr);
free_mem:
	kfree(dmn->send_ring->buf);
clean_qp:
	dr_destroy_qp(dmn->mdev, dmn->send_ring->qp);
clean_cq:
	dr_destroy_cq(dmn->mdev, dmn->send_ring->cq);
free_send_ring:
	kfree(dmn->send_ring);

	return ret;
}