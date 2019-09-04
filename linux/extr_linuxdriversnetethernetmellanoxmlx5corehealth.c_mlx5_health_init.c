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
struct mlx5_core_health {int /*<<< orphan*/  recover_work; int /*<<< orphan*/  work; int /*<<< orphan*/  wq_lock; int /*<<< orphan*/  wq; } ;
struct TYPE_4__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {TYPE_1__* pdev; TYPE_2__ priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  health_care ; 
 int /*<<< orphan*/  health_recover ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int mlx5_health_init(struct mlx5_core_dev *dev)
{
	struct mlx5_core_health *health;
	char *name;

	health = &dev->priv.health;
	name = kmalloc(64, GFP_KERNEL);
	if (!name)
		return -ENOMEM;

	strcpy(name, "mlx5_health");
	strcat(name, dev_name(&dev->pdev->dev));
	health->wq = create_singlethread_workqueue(name);
	kfree(name);
	if (!health->wq)
		return -ENOMEM;
	spin_lock_init(&health->wq_lock);
	INIT_WORK(&health->work, health_care);
	INIT_DELAYED_WORK(&health->recover_work, health_recover);

	return 0;
}