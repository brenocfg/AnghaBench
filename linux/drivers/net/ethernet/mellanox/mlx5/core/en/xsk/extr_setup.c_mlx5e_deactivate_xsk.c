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
struct mlx5e_channel {int /*<<< orphan*/  xskicosq; int /*<<< orphan*/  xskrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_deactivate_icosq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_deactivate_rq (int /*<<< orphan*/ *) ; 

void mlx5e_deactivate_xsk(struct mlx5e_channel *c)
{
	mlx5e_deactivate_rq(&c->xskrq);
	/* TX queue is disabled on close. */
	mlx5e_deactivate_icosq(&c->xskicosq);
}