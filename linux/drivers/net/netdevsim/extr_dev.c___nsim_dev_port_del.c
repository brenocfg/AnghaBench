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
struct devlink_port {int dummy; } ;
struct nsim_dev_port {int /*<<< orphan*/  ns; int /*<<< orphan*/  list; struct devlink_port devlink_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_port_type_clear (struct devlink_port*) ; 
 int /*<<< orphan*/  devlink_port_unregister (struct devlink_port*) ; 
 int /*<<< orphan*/  kfree (struct nsim_dev_port*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsim_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_dev_port_debugfs_exit (struct nsim_dev_port*) ; 

__attribute__((used)) static void __nsim_dev_port_del(struct nsim_dev_port *nsim_dev_port)
{
	struct devlink_port *devlink_port = &nsim_dev_port->devlink_port;

	list_del(&nsim_dev_port->list);
	devlink_port_type_clear(devlink_port);
	nsim_destroy(nsim_dev_port->ns);
	nsim_dev_port_debugfs_exit(nsim_dev_port);
	devlink_port_unregister(devlink_port);
	kfree(nsim_dev_port);
}