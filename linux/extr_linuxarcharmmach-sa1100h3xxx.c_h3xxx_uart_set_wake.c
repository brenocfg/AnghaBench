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
typedef  scalar_t__ u_int ;
struct uart_port {scalar_t__ mapbase; } ;

/* Variables and functions */
 int EINVAL ; 
 int PWER ; 
 int PWER_GPIO23 ; 
 int PWER_GPIO25 ; 
 scalar_t__ _Ser3UTCR0 ; 

__attribute__((used)) static int h3xxx_uart_set_wake(struct uart_port *port, u_int enable)
{
	int err = -EINVAL;

	if (port->mapbase == _Ser3UTCR0) {
		if (enable)
			PWER |= PWER_GPIO23 | PWER_GPIO25; /* DCD and CTS */
		else
			PWER &= ~(PWER_GPIO23 | PWER_GPIO25); /* DCD and CTS */
		err = 0;
	}
	return err;
}