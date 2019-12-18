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
struct sdw_slave {int const status; TYPE_1__* bus; } ;
struct sdw_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_lock; int /*<<< orphan*/  assigned; } ;
typedef  enum sdw_slave_status { ____Placeholder_sdw_slave_status } sdw_slave_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SDW_MAX_DEVICES ; 
#define  SDW_SLAVE_ALERT 130 
#define  SDW_SLAVE_ATTACHED 129 
#define  SDW_SLAVE_UNATTACHED 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sdw_slave* sdw_get_slave (struct sdw_bus*,int) ; 
 int sdw_handle_slave_alerts (struct sdw_slave*) ; 
 int sdw_initialize_slave (struct sdw_slave*) ; 
 int /*<<< orphan*/  sdw_modify_slave_status (struct sdw_slave*,int const) ; 
 int sdw_program_device_num (struct sdw_bus*) ; 
 int sdw_update_slave_status (struct sdw_slave*,int) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

int sdw_handle_slave_status(struct sdw_bus *bus,
			    enum sdw_slave_status status[])
{
	enum sdw_slave_status prev_status;
	struct sdw_slave *slave;
	int i, ret = 0;

	if (status[0] == SDW_SLAVE_ATTACHED) {
		dev_dbg(bus->dev, "Slave attached, programming device number\n");
		ret = sdw_program_device_num(bus);
		if (ret)
			dev_err(bus->dev, "Slave attach failed: %d\n", ret);
		/*
		 * programming a device number will have side effects,
		 * so we deal with other devices at a later time
		 */
		return ret;
	}

	/* Continue to check other slave statuses */
	for (i = 1; i <= SDW_MAX_DEVICES; i++) {
		mutex_lock(&bus->bus_lock);
		if (test_bit(i, bus->assigned) == false) {
			mutex_unlock(&bus->bus_lock);
			continue;
		}
		mutex_unlock(&bus->bus_lock);

		slave = sdw_get_slave(bus, i);
		if (!slave)
			continue;

		switch (status[i]) {
		case SDW_SLAVE_UNATTACHED:
			if (slave->status == SDW_SLAVE_UNATTACHED)
				break;

			sdw_modify_slave_status(slave, SDW_SLAVE_UNATTACHED);
			break;

		case SDW_SLAVE_ALERT:
			ret = sdw_handle_slave_alerts(slave);
			if (ret)
				dev_err(bus->dev,
					"Slave %d alert handling failed: %d\n",
					i, ret);
			break;

		case SDW_SLAVE_ATTACHED:
			if (slave->status == SDW_SLAVE_ATTACHED)
				break;

			prev_status = slave->status;
			sdw_modify_slave_status(slave, SDW_SLAVE_ATTACHED);

			if (prev_status == SDW_SLAVE_ALERT)
				break;

			ret = sdw_initialize_slave(slave);
			if (ret)
				dev_err(bus->dev,
					"Slave %d initialization failed: %d\n",
					i, ret);

			break;

		default:
			dev_err(bus->dev, "Invalid slave %d status:%d\n",
				i, status[i]);
			break;
		}

		ret = sdw_update_slave_status(slave, status[i]);
		if (ret)
			dev_err(slave->bus->dev,
				"Update Slave status failed:%d\n", ret);
	}

	return ret;
}