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
struct mlx5_cqwq {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cqwq_get_ctr_wrap_cnt (struct mlx5_cqwq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 mlx5_cqwq_get_wrap_cnt(struct mlx5_cqwq *wq)
{
	return mlx5_cqwq_get_ctr_wrap_cnt(wq, wq->cc);
}