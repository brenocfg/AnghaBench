#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct u132_port {int Status; } ;
struct u132 {int num_ports; struct u132_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/ * portstatus; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  RH_PS_PPS ; 
 int /*<<< orphan*/  RH_PS_PSS ; 
#define  USB_PORT_FEAT_POWER 130 
#define  USB_PORT_FEAT_RESET 129 
#define  USB_PORT_FEAT_SUSPEND 128 
 TYPE_1__ roothub ; 
 int u132_roothub_portreset (struct u132*,int) ; 
 int u132_write_pcimem (struct u132*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u132_roothub_setportfeature(struct u132 *u132, u16 wValue,
	u16 wIndex)
{
	if (wIndex == 0 || wIndex > u132->num_ports) {
		return -EINVAL;
	} else {
		int port_index = wIndex - 1;
		struct u132_port *port = &u132->port[port_index];
		port->Status &= ~(1 << wValue);
		switch (wValue) {
		case USB_PORT_FEAT_SUSPEND:
			return u132_write_pcimem(u132,
			       roothub.portstatus[port_index], RH_PS_PSS);
		case USB_PORT_FEAT_POWER:
			return u132_write_pcimem(u132,
			       roothub.portstatus[port_index], RH_PS_PPS);
		case USB_PORT_FEAT_RESET:
			return u132_roothub_portreset(u132, port_index);
		default:
			return -EPIPE;
		}
	}
}