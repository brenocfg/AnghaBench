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
struct mlx5e_channel {int num_tc; int /*<<< orphan*/  ix; int /*<<< orphan*/  cpu; int /*<<< orphan*/  netdev; int /*<<< orphan*/  rq; int /*<<< orphan*/ * sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cpu_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_activate_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_txqsq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_activate_channel(struct mlx5e_channel *c)
{
	int tc;

	for (tc = 0; tc < c->num_tc; tc++)
		mlx5e_activate_txqsq(&c->sq[tc]);
	mlx5e_activate_rq(&c->rq);
	netif_set_xps_queue(c->netdev, get_cpu_mask(c->cpu), c->ix);
}