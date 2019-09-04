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
struct mlx5_ib_mr {scalar_t__ ndescs; scalar_t__ max_descs; int /*<<< orphan*/ * descs; } ;
struct ib_mr {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX5_EN_RD ; 
 int MLX5_EN_WR ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 struct mlx5_ib_mr* to_mmr (struct ib_mr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct mlx5_ib_mr *mr = to_mmr(ibmr);
	__be64 *descs;

	if (unlikely(mr->ndescs == mr->max_descs))
		return -ENOMEM;

	descs = mr->descs;
	descs[mr->ndescs++] = cpu_to_be64(addr | MLX5_EN_RD | MLX5_EN_WR);

	return 0;
}