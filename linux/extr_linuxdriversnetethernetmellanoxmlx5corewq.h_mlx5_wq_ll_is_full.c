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
struct TYPE_2__ {scalar_t__ sz_m1; } ;
struct mlx5_wq_ll {scalar_t__ cur_sz; TYPE_1__ fbc; } ;

/* Variables and functions */

__attribute__((used)) static inline int mlx5_wq_ll_is_full(struct mlx5_wq_ll *wq)
{
	return wq->cur_sz == wq->fbc.sz_m1;
}