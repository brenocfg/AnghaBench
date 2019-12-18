#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_wqe_frag_info {scalar_t__ offset; int last_in_page; int /*<<< orphan*/ * di; } ;
struct mlx5e_rq_frag_info {scalar_t__ frag_stride; } ;
struct TYPE_3__ {int log_num_frags; int num_frags; struct mlx5e_rq_frag_info* arr; } ;
struct TYPE_4__ {TYPE_1__ info; struct mlx5e_wqe_frag_info* frags; int /*<<< orphan*/  wq; int /*<<< orphan*/ * di; } ;
struct mlx5e_rq {TYPE_2__ wqe; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int mlx5_wq_cyc_get_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_init_frags_partition(struct mlx5e_rq *rq)
{
	struct mlx5e_wqe_frag_info next_frag = {};
	struct mlx5e_wqe_frag_info *prev = NULL;
	int i;

	next_frag.di = &rq->wqe.di[0];

	for (i = 0; i < mlx5_wq_cyc_get_size(&rq->wqe.wq); i++) {
		struct mlx5e_rq_frag_info *frag_info = &rq->wqe.info.arr[0];
		struct mlx5e_wqe_frag_info *frag =
			&rq->wqe.frags[i << rq->wqe.info.log_num_frags];
		int f;

		for (f = 0; f < rq->wqe.info.num_frags; f++, frag++) {
			if (next_frag.offset + frag_info[f].frag_stride > PAGE_SIZE) {
				next_frag.di++;
				next_frag.offset = 0;
				if (prev)
					prev->last_in_page = true;
			}
			*frag = next_frag;

			/* prepare next */
			next_frag.offset += frag_info[f].frag_stride;
			prev = frag;
		}
	}

	if (prev)
		prev->last_in_page = true;
}