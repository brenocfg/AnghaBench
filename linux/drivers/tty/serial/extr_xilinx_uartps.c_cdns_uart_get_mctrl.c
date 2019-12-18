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
struct uart_port {struct cdns_uart* private_data; } ;
struct cdns_uart {scalar_t__ cts_override; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 

__attribute__((used)) static unsigned int cdns_uart_get_mctrl(struct uart_port *port)
{
	struct cdns_uart *cdns_uart_data = port->private_data;

	if (cdns_uart_data->cts_override)
		return 0;

	return TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
}