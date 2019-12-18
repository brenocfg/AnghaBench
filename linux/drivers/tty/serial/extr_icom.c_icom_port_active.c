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
struct icom_port {int port; scalar_t__ int_reg; scalar_t__ global_reg; } ;
struct icom_adapter {scalar_t__ version; scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ ADAPTER_V1 ; 

__attribute__((used)) static void icom_port_active(struct icom_port *icom_port, struct icom_adapter *icom_adapter, int port_num)
{
	if (icom_adapter->version == ADAPTER_V1) {
		icom_port->global_reg = icom_adapter->base_addr + 0x4000;
		icom_port->int_reg = icom_adapter->base_addr +
		    0x4004 + 2 - 2 * port_num;
	} else {
		icom_port->global_reg = icom_adapter->base_addr + 0x8000;
		if (icom_port->port < 2)
			icom_port->int_reg = icom_adapter->base_addr +
			    0x8004 + 2 - 2 * icom_port->port;
		else
			icom_port->int_reg = icom_adapter->base_addr +
			    0x8024 + 2 - 2 * (icom_port->port - 2);
	}
}