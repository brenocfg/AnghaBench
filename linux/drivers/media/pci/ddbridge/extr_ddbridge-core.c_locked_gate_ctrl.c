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
struct dvb_frontend {struct ddb_input* sec_priv; } ;
struct ddb_port {int /*<<< orphan*/  i2c_gate_lock; struct ddb_dvb* dvb; } ;
struct ddb_input {int nr; struct ddb_port* port; } ;
struct ddb_dvb {int (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dvb_frontend*,int) ; 
 int stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int locked_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct ddb_input *input = fe->sec_priv;
	struct ddb_port *port = input->port;
	struct ddb_dvb *dvb = &port->dvb[input->nr & 1];
	int status;

	if (enable) {
		mutex_lock(&port->i2c_gate_lock);
		status = dvb->i2c_gate_ctrl(fe, 1);
	} else {
		status = dvb->i2c_gate_ctrl(fe, 0);
		mutex_unlock(&port->i2c_gate_lock);
	}
	return status;
}