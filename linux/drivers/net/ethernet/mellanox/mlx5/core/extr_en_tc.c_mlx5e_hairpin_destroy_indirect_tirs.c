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
struct mlx5e_hairpin {int /*<<< orphan*/ * indir_tirn; int /*<<< orphan*/  func_mdev; } ;

/* Variables and functions */
 int MLX5E_NUM_INDIR_TIRS ; 
 int /*<<< orphan*/  mlx5_core_destroy_tir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_hairpin_destroy_indirect_tirs(struct mlx5e_hairpin *hp)
{
	int tt;

	for (tt = 0; tt < MLX5E_NUM_INDIR_TIRS; tt++)
		mlx5_core_destroy_tir(hp->func_mdev, hp->indir_tirn[tt]);
}