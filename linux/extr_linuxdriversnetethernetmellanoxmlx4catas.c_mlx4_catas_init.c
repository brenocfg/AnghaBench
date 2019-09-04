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
struct TYPE_2__ {int /*<<< orphan*/  catas_wq; int /*<<< orphan*/  catas_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catas_reset ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 

int  mlx4_catas_init(struct mlx4_dev *dev)
{
	INIT_WORK(&dev->persist->catas_work, catas_reset);
	dev->persist->catas_wq = create_singlethread_workqueue("mlx4_health");
	if (!dev->persist->catas_wq)
		return -ENOMEM;

	return 0;
}