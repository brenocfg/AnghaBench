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
struct mlx5_events {int /*<<< orphan*/  pcie_core_work; int /*<<< orphan*/  wq; struct mlx5_core_dev* dev; int /*<<< orphan*/  nh; } ;
struct TYPE_2__ {struct mlx5_events* events; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 struct mlx5_events* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_pcie_event ; 

int mlx5_events_init(struct mlx5_core_dev *dev)
{
	struct mlx5_events *events = kzalloc(sizeof(*events), GFP_KERNEL);

	if (!events)
		return -ENOMEM;

	ATOMIC_INIT_NOTIFIER_HEAD(&events->nh);
	events->dev = dev;
	dev->priv.events = events;
	events->wq = create_singlethread_workqueue("mlx5_events");
	if (!events->wq)
		return -ENOMEM;
	INIT_WORK(&events->pcie_core_work, mlx5_pcie_event);

	return 0;
}