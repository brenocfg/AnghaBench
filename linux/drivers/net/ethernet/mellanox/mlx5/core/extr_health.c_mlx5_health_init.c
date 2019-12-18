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
struct mlx5_core_health {int /*<<< orphan*/  report_work; int /*<<< orphan*/  fatal_report_work; int /*<<< orphan*/  wq_lock; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {int /*<<< orphan*/  device; TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fw_fatal_reporter_err_work ; 
 int /*<<< orphan*/  mlx5_fw_reporter_err_work ; 
 int /*<<< orphan*/  mlx5_fw_reporters_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fw_reporters_destroy (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int mlx5_health_init(struct mlx5_core_dev *dev)
{
	struct mlx5_core_health *health;
	char *name;

	mlx5_fw_reporters_create(dev);

	health = &dev->priv.health;
	name = kmalloc(64, GFP_KERNEL);
	if (!name)
		goto out_err;

	strcpy(name, "mlx5_health");
	strcat(name, dev_name(dev->device));
	health->wq = create_singlethread_workqueue(name);
	kfree(name);
	if (!health->wq)
		goto out_err;
	spin_lock_init(&health->wq_lock);
	INIT_WORK(&health->fatal_report_work, mlx5_fw_fatal_reporter_err_work);
	INIT_WORK(&health->report_work, mlx5_fw_reporter_err_work);

	return 0;

out_err:
	mlx5_fw_reporters_destroy(dev);
	return -ENOMEM;
}