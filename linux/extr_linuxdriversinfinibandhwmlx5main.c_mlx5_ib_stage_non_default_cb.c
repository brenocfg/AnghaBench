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
struct TYPE_2__ {int /*<<< orphan*/  query_port; int /*<<< orphan*/  get_port_immutable; } ;
struct mlx5_ib_dev {TYPE_1__ ib_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_ib_query_port ; 
 int /*<<< orphan*/  mlx5_port_immutable ; 

__attribute__((used)) static int mlx5_ib_stage_non_default_cb(struct mlx5_ib_dev *dev)
{
	dev->ib_dev.get_port_immutable  = mlx5_port_immutable;
	dev->ib_dev.query_port		= mlx5_ib_query_port;

	return 0;
}