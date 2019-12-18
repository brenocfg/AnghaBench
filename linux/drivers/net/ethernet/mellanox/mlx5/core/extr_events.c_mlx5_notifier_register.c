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
struct notifier_block {int dummy; } ;
struct mlx5_events {int /*<<< orphan*/  nh; } ;
struct TYPE_2__ {struct mlx5_events* events; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int atomic_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int mlx5_notifier_register(struct mlx5_core_dev *dev, struct notifier_block *nb)
{
	struct mlx5_events *events = dev->priv.events;

	return atomic_notifier_chain_register(&events->nh, nb);
}