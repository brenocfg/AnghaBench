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
struct mlx5_ib_dev {int num_ports; TYPE_1__* port; int /*<<< orphan*/  mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  offsets; int /*<<< orphan*/  names; int /*<<< orphan*/  set_id; scalar_t__ set_id_valid; } ;
struct TYPE_3__ {TYPE_2__ cnts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_q_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_ib_dealloc_counters(struct mlx5_ib_dev *dev)
{
	int i;

	for (i = 0; i < dev->num_ports; i++) {
		if (dev->port[i].cnts.set_id_valid)
			mlx5_core_dealloc_q_counter(dev->mdev,
						    dev->port[i].cnts.set_id);
		kfree(dev->port[i].cnts.names);
		kfree(dev->port[i].cnts.offsets);
	}
}