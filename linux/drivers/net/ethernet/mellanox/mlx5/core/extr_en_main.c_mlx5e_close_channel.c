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
struct mlx5e_channel {int /*<<< orphan*/  napi; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CHANNEL_STATE_XSK ; 
 int /*<<< orphan*/  kvfree (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_queues (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_xsk (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_free_xps_cpumask (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_close_channel(struct mlx5e_channel *c)
{
	if (test_bit(MLX5E_CHANNEL_STATE_XSK, c->state))
		mlx5e_close_xsk(c);
	mlx5e_close_queues(c);
	netif_napi_del(&c->napi);
	mlx5e_free_xps_cpumask(c);

	kvfree(c);
}