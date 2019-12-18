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
struct nsim_trap_item {int /*<<< orphan*/  action; void* trap_ctx; } ;
struct nsim_dev {int dummy; } ;
struct devlink_trap {int /*<<< orphan*/  init_action; int /*<<< orphan*/  id; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ WARN_ON (int) ; 
 struct nsim_dev* devlink_priv (struct devlink*) ; 
 struct nsim_trap_item* nsim_dev_trap_item_lookup (struct nsim_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsim_dev_devlink_trap_init(struct devlink *devlink,
				      const struct devlink_trap *trap,
				      void *trap_ctx)
{
	struct nsim_dev *nsim_dev = devlink_priv(devlink);
	struct nsim_trap_item *nsim_trap_item;

	nsim_trap_item = nsim_dev_trap_item_lookup(nsim_dev, trap->id);
	if (WARN_ON(!nsim_trap_item))
		return -ENOENT;

	nsim_trap_item->trap_ctx = trap_ctx;
	nsim_trap_item->action = trap->init_action;

	return 0;
}