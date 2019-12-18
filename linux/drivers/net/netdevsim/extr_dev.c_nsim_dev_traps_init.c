#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nsim_trap_item {int dummy; } ;
struct nsim_trap_data {struct nsim_trap_data* trap_items_arr; int /*<<< orphan*/  trap_report_dw; struct nsim_dev* nsim_dev; int /*<<< orphan*/  trap_lock; } ;
struct nsim_dev {struct nsim_trap_data* trap_data; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSIM_TRAP_REPORT_INTERVAL_MS ; 
 struct nsim_dev* devlink_priv (struct devlink*) ; 
 int devlink_traps_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nsim_trap_data* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nsim_trap_data*) ; 
 struct nsim_trap_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_dev_trap_report_work ; 
 int /*<<< orphan*/  nsim_traps_arr ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nsim_dev_traps_init(struct devlink *devlink)
{
	struct nsim_dev *nsim_dev = devlink_priv(devlink);
	struct nsim_trap_data *nsim_trap_data;
	int err;

	nsim_trap_data = kzalloc(sizeof(*nsim_trap_data), GFP_KERNEL);
	if (!nsim_trap_data)
		return -ENOMEM;

	nsim_trap_data->trap_items_arr = kcalloc(ARRAY_SIZE(nsim_traps_arr),
						 sizeof(struct nsim_trap_item),
						 GFP_KERNEL);
	if (!nsim_trap_data->trap_items_arr) {
		err = -ENOMEM;
		goto err_trap_data_free;
	}

	/* The lock is used to protect the action state of the registered
	 * traps. The value is written by user and read in delayed work when
	 * iterating over all the traps.
	 */
	spin_lock_init(&nsim_trap_data->trap_lock);
	nsim_trap_data->nsim_dev = nsim_dev;
	nsim_dev->trap_data = nsim_trap_data;

	err = devlink_traps_register(devlink, nsim_traps_arr,
				     ARRAY_SIZE(nsim_traps_arr), NULL);
	if (err)
		goto err_trap_items_free;

	INIT_DELAYED_WORK(&nsim_dev->trap_data->trap_report_dw,
			  nsim_dev_trap_report_work);
	schedule_delayed_work(&nsim_dev->trap_data->trap_report_dw,
			      msecs_to_jiffies(NSIM_TRAP_REPORT_INTERVAL_MS));

	return 0;

err_trap_items_free:
	kfree(nsim_trap_data->trap_items_arr);
err_trap_data_free:
	kfree(nsim_trap_data);
	return err;
}