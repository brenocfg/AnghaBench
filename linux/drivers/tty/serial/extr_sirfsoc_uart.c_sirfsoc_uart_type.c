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
struct uart_port {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SIRFSOC_PORT_TYPE ; 
 char const* SIRFUART_PORT_NAME ; 

__attribute__((used)) static const char *sirfsoc_uart_type(struct uart_port *port)
{
	return port->type == SIRFSOC_PORT_TYPE ? SIRFUART_PORT_NAME : NULL;
}