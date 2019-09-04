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
struct TYPE_6__ {int head; int tail; struct mlx5e_dma_info* page_cache; } ;
struct TYPE_5__ {int /*<<< orphan*/  frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
struct mlx5e_rq {int wq_type; int /*<<< orphan*/  wq_ctrl; TYPE_3__ page_cache; TYPE_2__ wqe; int /*<<< orphan*/  umr_mkey; int /*<<< orphan*/  mdev; TYPE_1__ mpwqe; scalar_t__ page_pool; int /*<<< orphan*/  xdp_rxq; scalar_t__ xdp_prog; } ;
struct mlx5e_dma_info {int dummy; } ;

/* Variables and functions */
 int MLX5E_CACHE_SIZE ; 
#define  MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ 128 
 int /*<<< orphan*/  bpf_prog_put (scalar_t__) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_free_di_list (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_page_release (struct mlx5e_rq*,struct mlx5e_dma_info*,int) ; 
 int /*<<< orphan*/  page_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_free_rq(struct mlx5e_rq *rq)
{
	int i;

	if (rq->xdp_prog)
		bpf_prog_put(rq->xdp_prog);

	xdp_rxq_info_unreg(&rq->xdp_rxq);
	if (rq->page_pool)
		page_pool_destroy(rq->page_pool);

	switch (rq->wq_type) {
	case MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		kvfree(rq->mpwqe.info);
		mlx5_core_destroy_mkey(rq->mdev, &rq->umr_mkey);
		break;
	default: /* MLX5_WQ_TYPE_CYCLIC */
		kvfree(rq->wqe.frags);
		mlx5e_free_di_list(rq);
	}

	for (i = rq->page_cache.head; i != rq->page_cache.tail;
	     i = (i + 1) & (MLX5E_CACHE_SIZE - 1)) {
		struct mlx5e_dma_info *dma_info = &rq->page_cache.page_cache[i];

		mlx5e_page_release(rq, dma_info, false);
	}
	mlx5_wq_destroy(&rq->wq_ctrl);
}