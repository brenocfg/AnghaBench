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
struct mlx5e_hairpin {int num_channels; int /*<<< orphan*/  pair; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct mlx5e_hairpin*) ; 
 int /*<<< orphan*/  mlx5_core_hairpin_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_hairpin_destroy_transport (struct mlx5e_hairpin*) ; 
 int /*<<< orphan*/  mlx5e_hairpin_rss_cleanup (struct mlx5e_hairpin*) ; 

__attribute__((used)) static void mlx5e_hairpin_destroy(struct mlx5e_hairpin *hp)
{
	if (hp->num_channels > 1)
		mlx5e_hairpin_rss_cleanup(hp);
	mlx5e_hairpin_destroy_transport(hp);
	mlx5_core_hairpin_destroy(hp->pair);
	kvfree(hp);
}