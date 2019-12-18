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
typedef  int u8 ;
struct opa_vnic_vema_port {int dummy; } ;
struct opa_vnic_ctrl_port {int num_ports; } ;

/* Variables and functions */

__attribute__((used)) static struct opa_vnic_vema_port *
vema_get_port(struct opa_vnic_ctrl_port *cport, u8 port_num)
{
	struct opa_vnic_vema_port *port = (void *)cport + sizeof(*cport);

	if (port_num > cport->num_ports)
		return NULL;

	return port + (port_num - 1);
}