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
struct mlx5e_wqe_frag_info {int dummy; } ;
struct mlx5e_rq {int dummy; } ;

/* Variables and functions */
 struct mlx5e_wqe_frag_info* get_frag (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_free_rx_wqe (struct mlx5e_rq*,struct mlx5e_wqe_frag_info*,int) ; 

void mlx5e_dealloc_rx_wqe(struct mlx5e_rq *rq, u16 ix)
{
	struct mlx5e_wqe_frag_info *wi = get_frag(rq, ix);

	mlx5e_free_rx_wqe(rq, wi, false);
}