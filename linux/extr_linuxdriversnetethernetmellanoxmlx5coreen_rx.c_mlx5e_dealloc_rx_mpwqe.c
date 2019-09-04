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
typedef  size_t u16 ;
struct TYPE_2__ {struct mlx5e_mpw_info* info; } ;
struct mlx5e_rq {TYPE_1__ mpwqe; } ;
struct mlx5e_mpw_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_free_rx_mpwqe (struct mlx5e_rq*,struct mlx5e_mpw_info*,int) ; 

void mlx5e_dealloc_rx_mpwqe(struct mlx5e_rq *rq, u16 ix)
{
	struct mlx5e_mpw_info *wi = &rq->mpwqe.info[ix];
	/* Don't recycle, this function is called on rq/netdev close */
	mlx5e_free_rx_mpwqe(rq, wi, false);
}