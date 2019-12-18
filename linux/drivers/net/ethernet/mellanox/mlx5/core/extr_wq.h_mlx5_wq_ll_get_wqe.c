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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_wq_ll {int /*<<< orphan*/  fbc; } ;

/* Variables and functions */
 void* mlx5_frag_buf_get_wqe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *mlx5_wq_ll_get_wqe(struct mlx5_wq_ll *wq, u16 ix)
{
	return mlx5_frag_buf_get_wqe(&wq->fbc, ix);
}