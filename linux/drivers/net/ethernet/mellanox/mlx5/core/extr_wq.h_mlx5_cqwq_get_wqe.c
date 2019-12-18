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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int log_stride; } ;
struct mlx5_cqwq {TYPE_1__ fbc; } ;
struct mlx5_cqe64 {int dummy; } ;

/* Variables and functions */
 struct mlx5_cqe64* mlx5_frag_buf_get_wqe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mlx5_cqe64 *mlx5_cqwq_get_wqe(struct mlx5_cqwq *wq, u32 ix)
{
	struct mlx5_cqe64 *cqe = mlx5_frag_buf_get_wqe(&wq->fbc, ix);

	/* For 128B CQEs the data is in the last 64B */
	cqe += wq->fbc.log_stride == 7;

	return cqe;
}