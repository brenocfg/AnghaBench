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
struct mlx5_hairpin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_hairpin*) ; 
 int /*<<< orphan*/  mlx5_hairpin_destroy_queues (struct mlx5_hairpin*) ; 
 int /*<<< orphan*/  mlx5_hairpin_unpair_queues (struct mlx5_hairpin*) ; 

void mlx5_core_hairpin_destroy(struct mlx5_hairpin *hp)
{
	mlx5_hairpin_unpair_queues(hp);
	mlx5_hairpin_destroy_queues(hp);
	kfree(hp);
}