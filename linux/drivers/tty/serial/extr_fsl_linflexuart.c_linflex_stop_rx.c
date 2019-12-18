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
 unsigned long LINFLEXD_LINIER_DRIE ; 
 scalar_t__ LINIER ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void linflex_stop_rx(struct uart_port *port)
{
	unsigned long ier;

	ier = readl(port->membase + LINIER);
	writel(ier & ~LINFLEXD_LINIER_DRIE, port->membase + LINIER);
}