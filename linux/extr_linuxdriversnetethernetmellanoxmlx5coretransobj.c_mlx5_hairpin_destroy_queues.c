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
struct mlx5_hairpin {int num_channels; int /*<<< orphan*/ * sqn; int /*<<< orphan*/  peer_mdev; int /*<<< orphan*/  peer_gone; int /*<<< orphan*/ * rqn; int /*<<< orphan*/  func_mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_destroy_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_hairpin_destroy_queues(struct mlx5_hairpin *hp)
{
	int i;

	for (i = 0; i < hp->num_channels; i++) {
		mlx5_core_destroy_rq(hp->func_mdev, hp->rqn[i]);
		if (!hp->peer_gone)
			mlx5_core_destroy_sq(hp->peer_mdev, hp->sqn[i]);
	}
}