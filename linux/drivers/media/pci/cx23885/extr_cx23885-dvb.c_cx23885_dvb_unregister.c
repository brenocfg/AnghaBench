#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ frontend; } ;
struct vb2_dvb_frontend {TYPE_1__ dvb; } ;
struct TYPE_7__ {TYPE_2__* driver; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct cx23885_tsport {int /*<<< orphan*/ * gate_ctrl; int /*<<< orphan*/  nr; TYPE_4__* dev; struct i2c_client* i2c_client_demod; struct i2c_client* i2c_client_tuner; struct i2c_client* i2c_client_sec; struct i2c_client* i2c_client_ci; int /*<<< orphan*/  frontends; } ;
struct TYPE_8__ {int board; } ;
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
#define  CX23885_BOARD_NETUP_DUAL_DVBS2_CI 129 
#define  CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF 128 
 int /*<<< orphan*/  altera_ci_release (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netup_ci_exit (struct cx23885_tsport*) ; 
 struct vb2_dvb_frontend* vb2_dvb_get_frontend (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vb2_dvb_unregister_bus (int /*<<< orphan*/ *) ; 

int cx23885_dvb_unregister(struct cx23885_tsport *port)
{
	struct vb2_dvb_frontend *fe0;
	struct i2c_client *client;

	fe0 = vb2_dvb_get_frontend(&port->frontends, 1);

	if (fe0 && fe0->dvb.frontend)
		vb2_dvb_unregister_bus(&port->frontends);

	/* remove I2C client for CI */
	client = port->i2c_client_ci;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	/* remove I2C client for SEC */
	client = port->i2c_client_sec;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	/* remove I2C client for tuner */
	client = port->i2c_client_tuner;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	/* remove I2C client for demodulator */
	client = port->i2c_client_demod;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	switch (port->dev->board) {
	case CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		netup_ci_exit(port);
		break;
	case CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
		altera_ci_release(port->dev, port->nr);
		break;
	}

	port->gate_ctrl = NULL;

	return 0;
}