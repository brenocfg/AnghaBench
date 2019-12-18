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
struct sdw_slave {int dev_num; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_SCP_DEVNUMBER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sdw_get_device_num (struct sdw_slave*) ; 
 int sdw_write (struct sdw_slave*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdw_assign_device_num(struct sdw_slave *slave)
{
	int ret, dev_num;

	/* check first if device number is assigned, if so reuse that */
	if (!slave->dev_num) {
		mutex_lock(&slave->bus->bus_lock);
		dev_num = sdw_get_device_num(slave);
		mutex_unlock(&slave->bus->bus_lock);
		if (dev_num < 0) {
			dev_err(slave->bus->dev, "Get dev_num failed: %d\n",
				dev_num);
			return dev_num;
		}
	} else {
		dev_info(slave->bus->dev,
			 "Slave already registered dev_num:%d\n",
			 slave->dev_num);

		/* Clear the slave->dev_num to transfer message on device 0 */
		dev_num = slave->dev_num;
		slave->dev_num = 0;
	}

	ret = sdw_write(slave, SDW_SCP_DEVNUMBER, dev_num);
	if (ret < 0) {
		dev_err(&slave->dev, "Program device_num %d failed: %d\n",
			dev_num, ret);
		return ret;
	}

	/* After xfer of msg, restore dev_num */
	slave->dev_num = dev_num;

	return 0;
}