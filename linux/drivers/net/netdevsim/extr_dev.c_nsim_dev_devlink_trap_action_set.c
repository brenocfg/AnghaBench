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
struct nsim_trap_item {int action; } ;
struct nsim_dev {TYPE_1__* trap_data; } ;
struct devlink_trap {int /*<<< orphan*/  id; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_trap_action { ____Placeholder_devlink_trap_action } devlink_trap_action ;
struct TYPE_2__ {int /*<<< orphan*/  trap_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ WARN_ON (int) ; 
 struct nsim_dev* devlink_priv (struct devlink*) ; 
 struct nsim_trap_item* nsim_dev_trap_item_lookup (struct nsim_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nsim_dev_devlink_trap_action_set(struct devlink *devlink,
				 const struct devlink_trap *trap,
				 enum devlink_trap_action action)
{
	struct nsim_dev *nsim_dev = devlink_priv(devlink);
	struct nsim_trap_item *nsim_trap_item;

	nsim_trap_item = nsim_dev_trap_item_lookup(nsim_dev, trap->id);
	if (WARN_ON(!nsim_trap_item))
		return -ENOENT;

	spin_lock(&nsim_dev->trap_data->trap_lock);
	nsim_trap_item->action = action;
	spin_unlock(&nsim_dev->trap_data->trap_lock);

	return 0;
}