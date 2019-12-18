#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct devlink_port {int dummy; } ;
struct nsim_dev_port {unsigned int port_index; int /*<<< orphan*/  list; TYPE_2__* ns; struct devlink_port devlink_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct nsim_dev {int /*<<< orphan*/  port_list; TYPE_1__ switch_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  devlink_port_attrs_set (struct devlink_port*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devlink_port_register (int /*<<< orphan*/ ,struct devlink_port*,unsigned int) ; 
 int /*<<< orphan*/  devlink_port_type_eth_set (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_unregister (struct devlink_port*) ; 
 int /*<<< orphan*/  kfree (struct nsim_dev_port*) ; 
 struct nsim_dev_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* nsim_create (struct nsim_dev*,struct nsim_dev_port*) ; 
 int /*<<< orphan*/  nsim_dev_port_debugfs_exit (struct nsim_dev_port*) ; 
 int nsim_dev_port_debugfs_init (struct nsim_dev*,struct nsim_dev_port*) ; 
 int /*<<< orphan*/  priv_to_devlink (struct nsim_dev*) ; 

__attribute__((used)) static int __nsim_dev_port_add(struct nsim_dev *nsim_dev,
			       unsigned int port_index)
{
	struct nsim_dev_port *nsim_dev_port;
	struct devlink_port *devlink_port;
	int err;

	nsim_dev_port = kzalloc(sizeof(*nsim_dev_port), GFP_KERNEL);
	if (!nsim_dev_port)
		return -ENOMEM;
	nsim_dev_port->port_index = port_index;

	devlink_port = &nsim_dev_port->devlink_port;
	devlink_port_attrs_set(devlink_port, DEVLINK_PORT_FLAVOUR_PHYSICAL,
			       port_index + 1, 0, 0,
			       nsim_dev->switch_id.id,
			       nsim_dev->switch_id.id_len);
	err = devlink_port_register(priv_to_devlink(nsim_dev), devlink_port,
				    port_index);
	if (err)
		goto err_port_free;

	err = nsim_dev_port_debugfs_init(nsim_dev, nsim_dev_port);
	if (err)
		goto err_dl_port_unregister;

	nsim_dev_port->ns = nsim_create(nsim_dev, nsim_dev_port);
	if (IS_ERR(nsim_dev_port->ns)) {
		err = PTR_ERR(nsim_dev_port->ns);
		goto err_port_debugfs_exit;
	}

	devlink_port_type_eth_set(devlink_port, nsim_dev_port->ns->netdev);
	list_add(&nsim_dev_port->list, &nsim_dev->port_list);

	return 0;

err_port_debugfs_exit:
	nsim_dev_port_debugfs_exit(nsim_dev_port);
err_dl_port_unregister:
	devlink_port_unregister(devlink_port);
err_port_free:
	kfree(nsim_dev_port);
	return err;
}