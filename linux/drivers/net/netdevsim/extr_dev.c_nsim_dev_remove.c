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
struct nsim_dev {int dummy; } ;
struct nsim_bus_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct nsim_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsim_dev_destroy (struct nsim_dev*) ; 
 int /*<<< orphan*/  nsim_dev_port_del_all (struct nsim_dev*) ; 

void nsim_dev_remove(struct nsim_bus_dev *nsim_bus_dev)
{
	struct nsim_dev *nsim_dev = dev_get_drvdata(&nsim_bus_dev->dev);

	nsim_dev_port_del_all(nsim_dev);
	nsim_dev_destroy(nsim_dev);
}