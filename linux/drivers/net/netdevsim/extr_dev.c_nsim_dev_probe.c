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
struct nsim_bus_dev {int port_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nsim_dev*) ; 
 int PTR_ERR (struct nsim_dev*) ; 
 int __nsim_dev_port_add (struct nsim_dev*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct nsim_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nsim_dev* nsim_dev_create (struct nsim_bus_dev*,int) ; 
 int /*<<< orphan*/  nsim_dev_destroy (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_port_del_all (struct nsim_dev*) ; 

int nsim_dev_probe(struct nsim_bus_dev *nsim_bus_dev)
{
	struct nsim_dev *nsim_dev;
	int i;
	int err;

	nsim_dev = nsim_dev_create(nsim_bus_dev, nsim_bus_dev->port_count);
	if (IS_ERR(nsim_dev))
		return PTR_ERR(nsim_dev);
	dev_set_drvdata(&nsim_bus_dev->dev, nsim_dev);

	mutex_lock(&nsim_dev->port_list_lock);
	for (i = 0; i < nsim_bus_dev->port_count; i++) {
		err = __nsim_dev_port_add(nsim_dev, i);
		if (err)
			goto err_port_del_all;
	}
	mutex_unlock(&nsim_dev->port_list_lock);
	return 0;

err_port_del_all:
	mutex_unlock(&nsim_dev->port_list_lock);
	nsim_dev_port_del_all(nsim_dev);
	nsim_dev_destroy(nsim_dev);
	return err;
}