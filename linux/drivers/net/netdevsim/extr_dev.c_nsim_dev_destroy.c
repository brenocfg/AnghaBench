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
struct nsim_dev {int /*<<< orphan*/  port_list_lock; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int /*<<< orphan*/  devlink_params_unregister (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_resources_unregister (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsim_bpf_dev_exit (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_debugfs_exit (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_dummy_region_exit (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_traps_exit (struct devlink*) ; 
 int /*<<< orphan*/  nsim_devlink_params ; 
 struct devlink* priv_to_devlink (struct nsim_dev*) ; 

__attribute__((used)) static void nsim_dev_destroy(struct nsim_dev *nsim_dev)
{
	struct devlink *devlink = priv_to_devlink(nsim_dev);

	nsim_bpf_dev_exit(nsim_dev);
	nsim_dev_debugfs_exit(nsim_dev);
	nsim_dev_traps_exit(devlink);
	nsim_dev_dummy_region_exit(nsim_dev);
	devlink_params_unregister(devlink, nsim_devlink_params,
				  ARRAY_SIZE(nsim_devlink_params));
	devlink_unregister(devlink);
	devlink_resources_unregister(devlink, NULL);
	mutex_destroy(&nsim_dev->port_list_lock);
	devlink_free(devlink);
}