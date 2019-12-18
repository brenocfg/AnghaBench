#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int clk_stop_timeout; } ;
struct sdw_slave {TYPE_3__ prop; TYPE_2__* bus; TYPE_1__* ops; } ;
struct sdw_driver {int (* probe ) (struct sdw_slave*,struct sdw_device_id const*) ;int /*<<< orphan*/  name; TYPE_1__* ops; } ;
struct sdw_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  clk_stop_timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read_prop ) (struct sdw_slave*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int dev_pm_domain_attach (struct device*,int) ; 
 int /*<<< orphan*/  dev_pm_domain_detach (struct device*,int) ; 
 struct sdw_slave* dev_to_sdw_dev (struct device*) ; 
 struct sdw_driver* drv_to_sdw_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sdw_device_id* sdw_get_device_id (struct sdw_slave*,struct sdw_driver*) ; 
 int stub1 (struct sdw_slave*,struct sdw_device_id const*) ; 
 int /*<<< orphan*/  stub2 (struct sdw_slave*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int sdw_drv_probe(struct device *dev)
{
	struct sdw_slave *slave = dev_to_sdw_dev(dev);
	struct sdw_driver *drv = drv_to_sdw_driver(dev->driver);
	const struct sdw_device_id *id;
	int ret;

	id = sdw_get_device_id(slave, drv);
	if (!id)
		return -ENODEV;

	slave->ops = drv->ops;

	/*
	 * attach to power domain but don't turn on (last arg)
	 */
	ret = dev_pm_domain_attach(dev, false);
	if (ret)
		return ret;

	ret = drv->probe(slave, id);
	if (ret) {
		dev_err(dev, "Probe of %s failed: %d\n", drv->name, ret);
		dev_pm_domain_detach(dev, false);
		return ret;
	}

	/* device is probed so let's read the properties now */
	if (slave->ops && slave->ops->read_prop)
		slave->ops->read_prop(slave);

	/*
	 * Check for valid clk_stop_timeout, use DisCo worst case value of
	 * 300ms
	 *
	 * TODO: check the timeouts and driver removal case
	 */
	if (slave->prop.clk_stop_timeout == 0)
		slave->prop.clk_stop_timeout = 300;

	slave->bus->clk_stop_timeout = max_t(u32, slave->bus->clk_stop_timeout,
					     slave->prop.clk_stop_timeout);

	return 0;
}