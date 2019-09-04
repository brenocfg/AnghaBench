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
typedef  int u32 ;
struct smi_port {int _dmaInterruptCH0; int _dmaInterruptCH1; int _int_status; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_port_clearInterrupt (struct smi_port*) ; 
 int /*<<< orphan*/  smi_port_disableInterrupt (struct smi_port*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smi_port_irq(struct smi_port *port, u32 int_status)
{
	u32 port_req_irq = port->_dmaInterruptCH0 | port->_dmaInterruptCH1;
	int handled = 0;

	if (int_status & port_req_irq) {
		smi_port_disableInterrupt(port);
		port->_int_status = int_status;
		smi_port_clearInterrupt(port);
		tasklet_schedule(&port->tasklet);
		handled = 1;
	}
	return handled;
}