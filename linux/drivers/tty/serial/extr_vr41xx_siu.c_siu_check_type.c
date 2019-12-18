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
struct uart_port {int line; scalar_t__ irq; } ;

/* Variables and functions */
 unsigned int PORT_UNKNOWN ; 
 unsigned int PORT_VR41XX_DSIU ; 
 unsigned int PORT_VR41XX_SIU ; 

__attribute__((used)) static inline unsigned int siu_check_type(struct uart_port *port)
{
	if (port->line == 0)
		return PORT_VR41XX_SIU;
	if (port->line == 1 && port->irq)
		return PORT_VR41XX_DSIU;

	return PORT_UNKNOWN;
}