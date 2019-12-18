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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 unsigned long LINFLEXD_LINIER_DTIE ; 
 scalar_t__ LINIER ; 
 int /*<<< orphan*/  linflex_transmit_buffer (struct uart_port*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void linflex_start_tx(struct uart_port *port)
{
	unsigned long ier;

	linflex_transmit_buffer(port);
	ier = readl(port->membase + LINIER);
	writel(ier | LINFLEXD_LINIER_DTIE, port->membase + LINIER);
}