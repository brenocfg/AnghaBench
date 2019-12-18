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
struct sdw_slave {int /*<<< orphan*/  node; scalar_t__ dev_num; struct sdw_bus* bus; } ;
struct sdw_bus {int /*<<< orphan*/  bus_lock; int /*<<< orphan*/  assigned; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sdw_slave* dev_to_sdw_dev (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_slave_debugfs_exit (struct sdw_slave*) ; 

__attribute__((used)) static int sdw_delete_slave(struct device *dev, void *data)
{
	struct sdw_slave *slave = dev_to_sdw_dev(dev);
	struct sdw_bus *bus = slave->bus;

	sdw_slave_debugfs_exit(slave);

	mutex_lock(&bus->bus_lock);

	if (slave->dev_num) /* clear dev_num if assigned */
		clear_bit(slave->dev_num, bus->assigned);

	list_del_init(&slave->node);
	mutex_unlock(&bus->bus_lock);

	device_unregister(dev);
	return 0;
}