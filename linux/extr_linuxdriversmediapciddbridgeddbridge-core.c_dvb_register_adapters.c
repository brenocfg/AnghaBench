#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_adapter {int dummy; } ;
struct ddb_port {int class; TYPE_2__* dvb; TYPE_1__* dev; } ;
struct ddb {int port_num; struct ddb_port* port; } ;
struct TYPE_4__ {int adap_registered; struct dvb_adapter* adap; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DDB_PORT_CI 130 
#define  DDB_PORT_LOOP 129 
#define  DDB_PORT_TUNER 128 
 int /*<<< orphan*/  THIS_MODULE ; 
 int adapter_alloc ; 
 int /*<<< orphan*/  adapter_nr ; 
 int dvb_register_adapter (struct dvb_adapter*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_register_adapters(struct ddb *dev)
{
	int i, ret = 0;
	struct ddb_port *port;
	struct dvb_adapter *adap;

	if (adapter_alloc == 3) {
		port = &dev->port[0];
		adap = port->dvb[0].adap;
		ret = dvb_register_adapter(adap, "DDBridge", THIS_MODULE,
					   port->dev->dev,
					   adapter_nr);
		if (ret < 0)
			return ret;
		port->dvb[0].adap_registered = 1;
		for (i = 0; i < dev->port_num; i++) {
			port = &dev->port[i];
			port->dvb[0].adap = adap;
			port->dvb[1].adap = adap;
		}
		return 0;
	}

	for (i = 0; i < dev->port_num; i++) {
		port = &dev->port[i];
		switch (port->class) {
		case DDB_PORT_TUNER:
			adap = port->dvb[0].adap;
			ret = dvb_register_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			if (ret < 0)
				return ret;
			port->dvb[0].adap_registered = 1;

			if (adapter_alloc > 0) {
				port->dvb[1].adap = port->dvb[0].adap;
				break;
			}
			adap = port->dvb[1].adap;
			ret = dvb_register_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			if (ret < 0)
				return ret;
			port->dvb[1].adap_registered = 1;
			break;

		case DDB_PORT_CI:
		case DDB_PORT_LOOP:
			adap = port->dvb[0].adap;
			ret = dvb_register_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			if (ret < 0)
				return ret;
			port->dvb[0].adap_registered = 1;
			break;
		default:
			if (adapter_alloc < 2)
				break;
			adap = port->dvb[0].adap;
			ret = dvb_register_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			if (ret < 0)
				return ret;
			port->dvb[0].adap_registered = 1;
			break;
		}
	}
	return ret;
}