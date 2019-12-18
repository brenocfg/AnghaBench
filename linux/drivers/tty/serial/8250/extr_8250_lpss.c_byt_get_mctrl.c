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
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_DSR ; 
 unsigned int serial8250_do_get_mctrl (struct uart_port*) ; 

__attribute__((used)) static unsigned int byt_get_mctrl(struct uart_port *port)
{
	unsigned int ret = serial8250_do_get_mctrl(port);

	/* Force DCD and DSR signals to permanently be reported as active */
	ret |= TIOCM_CAR | TIOCM_DSR;

	return ret;
}