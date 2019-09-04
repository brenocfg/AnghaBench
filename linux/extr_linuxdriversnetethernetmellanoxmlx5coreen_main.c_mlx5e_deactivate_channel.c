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
struct mlx5e_channel {int num_tc; int /*<<< orphan*/ * sq; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_deactivate_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_deactivate_txqsq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_deactivate_channel(struct mlx5e_channel *c)
{
	int tc;

	mlx5e_deactivate_rq(&c->rq);
	for (tc = 0; tc < c->num_tc; tc++)
		mlx5e_deactivate_txqsq(&c->sq[tc]);
}