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
struct mlx5_flow_steering {int /*<<< orphan*/  fgs_cache; } ;
struct mlx5_flow_group {int /*<<< orphan*/  ftes_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dealloc_flow_group(struct mlx5_flow_steering *steering,
			       struct mlx5_flow_group *fg)
{
	rhashtable_destroy(&fg->ftes_hash);
	kmem_cache_free(steering->fgs_cache, fg);
}