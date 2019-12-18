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
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct mlx5_ib_dev {TYPE_1__ mdev_events; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_ib_event ; 
 int /*<<< orphan*/  mlx5_notifier_register (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int mlx5_ib_stage_dev_notifier_init(struct mlx5_ib_dev *dev)
{
	dev->mdev_events.notifier_call = mlx5_ib_event;
	mlx5_notifier_register(dev->mdev, &dev->mdev_events);
	return 0;
}