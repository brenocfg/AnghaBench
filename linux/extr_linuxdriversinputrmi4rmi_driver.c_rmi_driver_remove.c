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
struct rmi_driver_data {int /*<<< orphan*/ * irqdomain; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmi_disable_irq (struct rmi_device*,int) ; 
 int /*<<< orphan*/  rmi_f34_remove_sysfs (struct rmi_device*) ; 
 int /*<<< orphan*/  rmi_free_function_list (struct rmi_device*) ; 
 struct rmi_device* to_rmi_device (struct device*) ; 

__attribute__((used)) static int rmi_driver_remove(struct device *dev)
{
	struct rmi_device *rmi_dev = to_rmi_device(dev);
	struct rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);

	rmi_disable_irq(rmi_dev, false);

	irq_domain_remove(data->irqdomain);
	data->irqdomain = NULL;

	rmi_f34_remove_sysfs(rmi_dev);
	rmi_free_function_list(rmi_dev);

	return 0;
}