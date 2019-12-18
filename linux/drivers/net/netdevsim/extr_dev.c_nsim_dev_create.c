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
struct TYPE_2__ {int id_len; int /*<<< orphan*/  id; } ;
struct nsim_dev {int fw_update_status; int /*<<< orphan*/  test1; int /*<<< orphan*/  max_macs; int /*<<< orphan*/  port_list_lock; int /*<<< orphan*/  port_list; TYPE_1__ switch_id; struct nsim_bus_dev* nsim_bus_dev; } ;
struct nsim_bus_dev {int /*<<< orphan*/  dev; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct nsim_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NSIM_DEV_MAX_MACS_DEFAULT ; 
 int /*<<< orphan*/  NSIM_DEV_TEST1_DEFAULT ; 
 struct devlink* devlink_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int /*<<< orphan*/  devlink_params_publish (struct devlink*) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_params_unregister (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nsim_dev* devlink_priv (struct devlink*) ; 
 int devlink_register (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_resources_unregister (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nsim_bpf_dev_init (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_debugfs_exit (struct nsim_dev*) ; 
 int nsim_dev_debugfs_init (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_devlink_ops ; 
 int /*<<< orphan*/  nsim_dev_dummy_region_exit (struct nsim_dev*) ; 
 int nsim_dev_dummy_region_init (struct nsim_dev*,struct devlink*) ; 
 int nsim_dev_resources_register (struct devlink*) ; 
 int /*<<< orphan*/  nsim_dev_traps_exit (struct devlink*) ; 
 int nsim_dev_traps_init (struct devlink*) ; 
 int /*<<< orphan*/  nsim_devlink_params ; 
 int /*<<< orphan*/  nsim_devlink_set_params_init_values (struct nsim_dev*,struct devlink*) ; 

__attribute__((used)) static struct nsim_dev *
nsim_dev_create(struct nsim_bus_dev *nsim_bus_dev, unsigned int port_count)
{
	struct nsim_dev *nsim_dev;
	struct devlink *devlink;
	int err;

	devlink = devlink_alloc(&nsim_dev_devlink_ops, sizeof(*nsim_dev));
	if (!devlink)
		return ERR_PTR(-ENOMEM);
	nsim_dev = devlink_priv(devlink);
	nsim_dev->nsim_bus_dev = nsim_bus_dev;
	nsim_dev->switch_id.id_len = sizeof(nsim_dev->switch_id.id);
	get_random_bytes(nsim_dev->switch_id.id, nsim_dev->switch_id.id_len);
	INIT_LIST_HEAD(&nsim_dev->port_list);
	mutex_init(&nsim_dev->port_list_lock);
	nsim_dev->fw_update_status = true;
	nsim_dev->max_macs = NSIM_DEV_MAX_MACS_DEFAULT;
	nsim_dev->test1 = NSIM_DEV_TEST1_DEFAULT;

	err = nsim_dev_resources_register(devlink);
	if (err)
		goto err_devlink_free;

	err = devlink_register(devlink, &nsim_bus_dev->dev);
	if (err)
		goto err_resources_unregister;

	err = devlink_params_register(devlink, nsim_devlink_params,
				      ARRAY_SIZE(nsim_devlink_params));
	if (err)
		goto err_dl_unregister;
	nsim_devlink_set_params_init_values(nsim_dev, devlink);

	err = nsim_dev_dummy_region_init(nsim_dev, devlink);
	if (err)
		goto err_params_unregister;

	err = nsim_dev_traps_init(devlink);
	if (err)
		goto err_dummy_region_exit;

	err = nsim_dev_debugfs_init(nsim_dev);
	if (err)
		goto err_traps_exit;

	err = nsim_bpf_dev_init(nsim_dev);
	if (err)
		goto err_debugfs_exit;

	devlink_params_publish(devlink);
	return nsim_dev;

err_debugfs_exit:
	nsim_dev_debugfs_exit(nsim_dev);
err_traps_exit:
	nsim_dev_traps_exit(devlink);
err_dummy_region_exit:
	nsim_dev_dummy_region_exit(nsim_dev);
err_params_unregister:
	devlink_params_unregister(devlink, nsim_devlink_params,
				  ARRAY_SIZE(nsim_devlink_params));
err_dl_unregister:
	devlink_unregister(devlink);
err_resources_unregister:
	devlink_resources_unregister(devlink, NULL);
err_devlink_free:
	devlink_free(devlink);
	return ERR_PTR(err);
}