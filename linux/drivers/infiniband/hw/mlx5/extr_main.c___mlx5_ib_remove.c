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
struct mlx5_ib_profile {TYPE_1__* stage; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct mlx5_ib_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_ib_dev*) ; 

void __mlx5_ib_remove(struct mlx5_ib_dev *dev,
		      const struct mlx5_ib_profile *profile,
		      int stage)
{
	/* Number of stages to cleanup */
	while (stage) {
		stage--;
		if (profile->stage[stage].cleanup)
			profile->stage[stage].cleanup(dev);
	}

	kfree(dev->port);
	ib_dealloc_device(&dev->ib_dev);
}