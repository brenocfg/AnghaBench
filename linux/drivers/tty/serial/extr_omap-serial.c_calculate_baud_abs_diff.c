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
struct uart_port {unsigned int uartclk; } ;

/* Variables and functions */

__attribute__((used)) static inline int calculate_baud_abs_diff(struct uart_port *port,
				unsigned int baud, unsigned int mode)
{
	unsigned int n = port->uartclk / (mode * baud);
	int abs_diff;

	if (n == 0)
		n = 1;

	abs_diff = baud - (port->uartclk / (mode * n));
	if (abs_diff < 0)
		abs_diff = -abs_diff;

	return abs_diff;
}