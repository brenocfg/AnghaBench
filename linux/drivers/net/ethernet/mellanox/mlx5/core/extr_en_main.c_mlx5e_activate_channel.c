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
struct mlx5e_channel {int num_tc; int /*<<< orphan*/  state; int /*<<< orphan*/  ix; int /*<<< orphan*/  xps_cpumask; int /*<<< orphan*/  netdev; int /*<<< orphan*/  rq; int /*<<< orphan*/  icosq; int /*<<< orphan*/ * sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CHANNEL_STATE_XSK ; 
 int /*<<< orphan*/  mlx5e_activate_icosq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_txqsq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_xsk (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_activate_channel(struct mlx5e_channel *c)
{
	int tc;

	for (tc = 0; tc < c->num_tc; tc++)
		mlx5e_activate_txqsq(&c->sq[tc]);
	mlx5e_activate_icosq(&c->icosq);
	mlx5e_activate_rq(&c->rq);
	netif_set_xps_queue(c->netdev, c->xps_cpumask, c->ix);

	if (test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
		mlx5e_activate_xsk(c);
}