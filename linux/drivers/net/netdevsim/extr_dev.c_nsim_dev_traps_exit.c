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
struct nsim_dev {TYPE_1__* trap_data; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {struct TYPE_2__* trap_items_arr; int /*<<< orphan*/  trap_report_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct nsim_dev* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  devlink_traps_unregister (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  nsim_traps_arr ; 

__attribute__((used)) static void nsim_dev_traps_exit(struct devlink *devlink)
{
	struct nsim_dev *nsim_dev = devlink_priv(devlink);

	cancel_delayed_work_sync(&nsim_dev->trap_data->trap_report_dw);
	devlink_traps_unregister(devlink, nsim_traps_arr,
				 ARRAY_SIZE(nsim_traps_arr));
	kfree(nsim_dev->trap_data->trap_items_arr);
	kfree(nsim_dev->trap_data);
}