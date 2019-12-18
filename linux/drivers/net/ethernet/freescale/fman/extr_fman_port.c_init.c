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
struct fman_port {int port_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FMAN_PORT_TYPE_RX 129 
#define  FMAN_PORT_TYPE_TX 128 
 int init_bmi_rx (struct fman_port*) ; 
 int init_bmi_tx (struct fman_port*) ; 
 int /*<<< orphan*/  init_hwp (struct fman_port*) ; 
 int init_qmi (struct fman_port*) ; 

__attribute__((used)) static int init(struct fman_port *port)
{
	int err;

	/* Init BMI registers */
	switch (port->port_type) {
	case FMAN_PORT_TYPE_RX:
		err = init_bmi_rx(port);
		if (!err)
			init_hwp(port);
		break;
	case FMAN_PORT_TYPE_TX:
		err = init_bmi_tx(port);
		break;
	default:
		return -EINVAL;
	}

	if (err)
		return err;

	/* Init QMI registers */
	err = init_qmi(port);
	if (err)
		return err;

	return 0;
}