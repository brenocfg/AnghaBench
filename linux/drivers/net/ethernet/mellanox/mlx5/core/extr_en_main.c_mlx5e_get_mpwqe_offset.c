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
typedef  int u64 ;
typedef  int u16 ;
struct mlx5e_rq {int dummy; } ;

/* Variables and functions */
 int MLX5E_LOG_ALIGNED_MPWQE_PPW ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static inline u64 mlx5e_get_mpwqe_offset(struct mlx5e_rq *rq, u16 wqe_ix)
{
	return (wqe_ix << MLX5E_LOG_ALIGNED_MPWQE_PPW) << PAGE_SHIFT;
}