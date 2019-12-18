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
struct mlx5_cqwq {int dummy; } ;
struct mlx5_cqe64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_cqwq_ctr2ix (struct mlx5_cqwq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cqwq_get_wqe (struct mlx5_cqwq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5e_read_cqe_slot(struct mlx5_cqwq *wq,
				       u32 cqcc, void *data)
{
	u32 ci = mlx5_cqwq_ctr2ix(wq, cqcc);

	memcpy(data, mlx5_cqwq_get_wqe(wq, ci), sizeof(struct mlx5_cqe64));
}