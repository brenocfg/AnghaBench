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
typedef  size_t u16 ;
struct mlx5e_wqe_frag_info {int dummy; } ;
struct TYPE_3__ {size_t log_num_frags; } ;
struct TYPE_4__ {TYPE_1__ info; struct mlx5e_wqe_frag_info* frags; } ;
struct mlx5e_rq {TYPE_2__ wqe; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx5e_wqe_frag_info *get_frag(struct mlx5e_rq *rq, u16 ix)
{
	return &rq->wqe.frags[ix << rq->wqe.info.log_num_frags];
}