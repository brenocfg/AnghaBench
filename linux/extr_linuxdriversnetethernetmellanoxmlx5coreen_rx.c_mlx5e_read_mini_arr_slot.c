#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_cq {scalar_t__ mini_arr_idx; int /*<<< orphan*/  mini_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_read_cqe_slot (struct mlx5e_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5e_read_mini_arr_slot(struct mlx5e_cq *cq, u32 cqcc)
{
	mlx5e_read_cqe_slot(cq, cqcc, cq->mini_arr);
	cq->mini_arr_idx = 0;
}