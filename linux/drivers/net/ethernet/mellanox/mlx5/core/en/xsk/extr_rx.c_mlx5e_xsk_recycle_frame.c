#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mlx5e_rq {TYPE_1__* umem; } ;
struct TYPE_2__ {int chunk_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsk_umem_fq_reuse (TYPE_1__*,int) ; 

__attribute__((used)) static inline void mlx5e_xsk_recycle_frame(struct mlx5e_rq *rq, u64 handle)
{
	xsk_umem_fq_reuse(rq->umem, handle & rq->umem->chunk_mask);
}