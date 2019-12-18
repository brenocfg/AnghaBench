#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_lag {TYPE_1__* pf; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int MLX5_MAX_PORTS ; 
 int /*<<< orphan*/  mlx5_add_dev_by_protocol (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_lag_add_ib_devices(struct mlx5_lag *ldev)
{
	int i;

	for (i = 0; i < MLX5_MAX_PORTS; i++)
		if (ldev->pf[i].dev)
			mlx5_add_dev_by_protocol(ldev->pf[i].dev,
						 MLX5_INTERFACE_PROTOCOL_IB);
}