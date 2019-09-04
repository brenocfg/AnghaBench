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
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_2__ {int /*<<< orphan*/ * catas_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 

void mlx4_catas_end(struct mlx4_dev *dev)
{
	if (dev->persist->catas_wq) {
		destroy_workqueue(dev->persist->catas_wq);
		dev->persist->catas_wq = NULL;
	}
}