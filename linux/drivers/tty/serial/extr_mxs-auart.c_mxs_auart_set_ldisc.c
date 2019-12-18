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
struct uart_port {int /*<<< orphan*/  flags; } ;
struct ktermios {scalar_t__ c_line; } ;

/* Variables and functions */
 scalar_t__ N_PPS ; 
 int /*<<< orphan*/  UPF_HARDPPS_CD ; 
 int /*<<< orphan*/  mxs_auart_enable_ms (struct uart_port*) ; 

__attribute__((used)) static void mxs_auart_set_ldisc(struct uart_port *port,
				struct ktermios *termios)
{
	if (termios->c_line == N_PPS) {
		port->flags |= UPF_HARDPPS_CD;
		mxs_auart_enable_ms(port);
	} else {
		port->flags &= ~UPF_HARDPPS_CD;
	}
}