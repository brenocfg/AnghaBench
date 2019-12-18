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
typedef  int u32 ;
struct TYPE_2__ {int cons_index; } ;
struct mlx4_ib_cq {TYPE_1__ mcq; } ;

/* Variables and functions */
 scalar_t__ get_sw_cqe (struct mlx4_ib_cq*,int) ; 

__attribute__((used)) static int mlx4_ib_get_outstanding_cqes(struct mlx4_ib_cq *cq)
{
	u32 i;

	i = cq->mcq.cons_index;
	while (get_sw_cqe(cq, i))
		++i;

	return i - cq->mcq.cons_index;
}