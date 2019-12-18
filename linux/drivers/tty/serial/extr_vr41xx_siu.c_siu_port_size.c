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
struct uart_port {int type; } ;

/* Variables and functions */
#define  PORT_VR41XX_DSIU 129 
#define  PORT_VR41XX_SIU 128 

__attribute__((used)) static inline unsigned long siu_port_size(struct uart_port *port)
{
	switch (port->type) {
	case PORT_VR41XX_SIU:
		return 11UL;
	case PORT_VR41XX_DSIU:
		return 8UL;
	}

	return 0;
}