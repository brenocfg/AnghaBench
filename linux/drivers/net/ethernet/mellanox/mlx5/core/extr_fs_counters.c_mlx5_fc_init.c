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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fc_bulk {int dummy; } ;
struct mlx5_fc {int /*<<< orphan*/  id; struct mlx5_fc_bulk* bulk; } ;

/* Variables and functions */

__attribute__((used)) static void mlx5_fc_init(struct mlx5_fc *counter, struct mlx5_fc_bulk *bulk,
			 u32 id)
{
	counter->bulk = bulk;
	counter->id = id;
}