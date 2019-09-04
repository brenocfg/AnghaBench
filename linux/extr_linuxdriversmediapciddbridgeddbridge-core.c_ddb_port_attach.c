#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ddb_port {int class; int /*<<< orphan*/  nr; TYPE_2__* dev; scalar_t__ output; TYPE_1__* dvb; TYPE_3__** input; } ;
struct TYPE_7__ {struct TYPE_7__* redi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
#define  DDB_PORT_CI 130 
#define  DDB_PORT_LOOP 129 
#define  DDB_PORT_TUNER 128 
 int /*<<< orphan*/  DVB_DEVICE_SEC ; 
 int /*<<< orphan*/  ci_bitrate ; 
 int ddb_ci_attach (struct ddb_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dvb_input_attach (TYPE_3__*) ; 
 int /*<<< orphan*/  dvb_input_detach (TYPE_3__*) ; 
 int dvb_register_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbdev_ci ; 

__attribute__((used)) static int ddb_port_attach(struct ddb_port *port)
{
	int ret = 0;

	switch (port->class) {
	case DDB_PORT_TUNER:
		ret = dvb_input_attach(port->input[0]);
		if (ret < 0)
			break;
		ret = dvb_input_attach(port->input[1]);
		if (ret < 0) {
			dvb_input_detach(port->input[0]);
			break;
		}
		port->input[0]->redi = port->input[0];
		port->input[1]->redi = port->input[1];
		break;
	case DDB_PORT_CI:
		ret = ddb_ci_attach(port, ci_bitrate);
		if (ret < 0)
			break;
		/* fall-through */
	case DDB_PORT_LOOP:
		ret = dvb_register_device(port->dvb[0].adap,
					  &port->dvb[0].dev,
					  &dvbdev_ci, (void *)port->output,
					  DVB_DEVICE_SEC, 0);
		break;
	default:
		break;
	}
	if (ret < 0)
		dev_err(port->dev->dev, "port_attach on port %d failed\n",
			port->nr);
	return ret;
}