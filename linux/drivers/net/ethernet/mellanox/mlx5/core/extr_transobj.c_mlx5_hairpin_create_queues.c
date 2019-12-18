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
struct mlx5_hairpin_params {int dummy; } ;
struct mlx5_hairpin {int num_channels; int /*<<< orphan*/ * rqn; int /*<<< orphan*/  func_mdev; int /*<<< orphan*/ * sqn; int /*<<< orphan*/  peer_mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_destroy_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_hairpin_create_rq (int /*<<< orphan*/ ,struct mlx5_hairpin_params*,int /*<<< orphan*/ *) ; 
 int mlx5_hairpin_create_sq (int /*<<< orphan*/ ,struct mlx5_hairpin_params*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_hairpin_create_queues(struct mlx5_hairpin *hp,
				      struct mlx5_hairpin_params *params)
{
	int i, j, err;

	for (i = 0; i < hp->num_channels; i++) {
		err = mlx5_hairpin_create_rq(hp->func_mdev, params, &hp->rqn[i]);
		if (err)
			goto out_err_rq;
	}

	for (i = 0; i < hp->num_channels; i++) {
		err = mlx5_hairpin_create_sq(hp->peer_mdev, params, &hp->sqn[i]);
		if (err)
			goto out_err_sq;
	}

	return 0;

out_err_sq:
	for (j = 0; j < i; j++)
		mlx5_core_destroy_sq(hp->peer_mdev, hp->sqn[j]);
	i = hp->num_channels;
out_err_rq:
	for (j = 0; j < i; j++)
		mlx5_core_destroy_rq(hp->func_mdev, hp->rqn[j]);
	return err;
}