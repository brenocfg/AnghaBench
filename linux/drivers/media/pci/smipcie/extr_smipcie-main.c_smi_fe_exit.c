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
struct smi_port {int /*<<< orphan*/  fe; scalar_t__ i2c_client_demod; scalar_t__ i2c_client_tuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_del_i2c_client (scalar_t__) ; 

__attribute__((used)) static void smi_fe_exit(struct smi_port *port)
{
	dvb_unregister_frontend(port->fe);
	/* remove I2C demod and tuner */
	if (port->i2c_client_tuner)
		smi_del_i2c_client(port->i2c_client_tuner);
	if (port->i2c_client_demod)
		smi_del_i2c_client(port->i2c_client_demod);
	dvb_frontend_detach(port->fe);
}