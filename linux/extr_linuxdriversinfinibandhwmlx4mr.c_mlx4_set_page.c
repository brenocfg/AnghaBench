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
struct mlx4_ib_mr {scalar_t__ npages; scalar_t__ max_pages; int /*<<< orphan*/ * pages; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX4_MTT_FLAG_PRESENT ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 struct mlx4_ib_mr* to_mmr (struct ib_mr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx4_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct mlx4_ib_mr *mr = to_mmr(ibmr);

	if (unlikely(mr->npages == mr->max_pages))
		return -ENOMEM;

	mr->pages[mr->npages++] = cpu_to_be64(addr | MLX4_MTT_FLAG_PRESENT);

	return 0;
}