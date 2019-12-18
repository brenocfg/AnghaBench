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
struct ddb_port {scalar_t__ class; } ;
struct ddb {int port_num; int /*<<< orphan*/  dev; struct ddb_port* port; } ;

/* Variables and functions */
 scalar_t__ DDB_PORT_NONE ; 
 int ENODEV ; 
 int ddb_port_attach (struct ddb_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int dvb_register_adapters (struct ddb*) ; 

int ddb_ports_attach(struct ddb *dev)
{
	int i, numports, err_ports = 0, ret = 0;
	struct ddb_port *port;

	if (dev->port_num) {
		ret = dvb_register_adapters(dev);
		if (ret < 0) {
			dev_err(dev->dev, "Registering adapters failed. Check DVB_MAX_ADAPTERS in config.\n");
			return ret;
		}
	}

	numports = dev->port_num;

	for (i = 0; i < dev->port_num; i++) {
		port = &dev->port[i];
		if (port->class != DDB_PORT_NONE) {
			ret = ddb_port_attach(port);
			if (ret)
				err_ports++;
		} else {
			numports--;
		}
	}

	if (err_ports) {
		if (err_ports == numports) {
			dev_err(dev->dev, "All connected ports failed to initialise!\n");
			return -ENODEV;
		}

		dev_warn(dev->dev, "%d of %d connected ports failed to initialise!\n",
			 err_ports, numports);
	}

	return 0;
}