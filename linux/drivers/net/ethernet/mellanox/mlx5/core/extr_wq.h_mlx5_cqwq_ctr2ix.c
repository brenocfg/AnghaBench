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
struct TYPE_2__ {int sz_m1; } ;
struct mlx5_cqwq {TYPE_1__ fbc; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 mlx5_cqwq_ctr2ix(struct mlx5_cqwq *wq, u32 ctr)
{
	return ctr & wq->fbc.sz_m1;
}