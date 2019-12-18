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
 unsigned int UBRLCR_BREAK ; 
 scalar_t__ UBRLCR_OFFSET ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void uart_clps711x_break_ctl(struct uart_port *port, int break_state)
{
	unsigned int ubrlcr;

	ubrlcr = readl(port->membase + UBRLCR_OFFSET);
	if (break_state)
		ubrlcr |= UBRLCR_BREAK;
	else
		ubrlcr &= ~UBRLCR_BREAK;
	writel(ubrlcr, port->membase + UBRLCR_OFFSET);
}