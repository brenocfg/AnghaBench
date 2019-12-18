#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  drop_counter; } ;
struct TYPE_3__ {int /*<<< orphan*/  drop_counter; } ;
struct mlx5_vport {TYPE_2__ egress; TYPE_1__ ingress; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_fc_destroy (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esw_vport_destroy_drop_counters(struct mlx5_vport *vport)
{
	struct mlx5_core_dev *dev = vport->dev;

	if (vport->ingress.drop_counter)
		mlx5_fc_destroy(dev, vport->ingress.drop_counter);
	if (vport->egress.drop_counter)
		mlx5_fc_destroy(dev, vport->egress.drop_counter);
}