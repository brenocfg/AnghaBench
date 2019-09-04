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
struct TYPE_2__ {int /*<<< orphan*/  cons_index; } ;
struct mlx4_ib_cq {TYPE_1__ mcq; } ;
struct mlx4_cqe {int dummy; } ;

/* Variables and functions */
 struct mlx4_cqe* get_sw_cqe (struct mlx4_ib_cq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx4_cqe *next_cqe_sw(struct mlx4_ib_cq *cq)
{
	return get_sw_cqe(cq, cq->mcq.cons_index);
}