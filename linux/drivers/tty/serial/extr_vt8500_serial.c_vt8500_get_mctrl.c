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
 unsigned int TIOCM_CTS ; 
 int /*<<< orphan*/  VT8500_URUSR ; 
 unsigned int vt8500_read (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int vt8500_get_mctrl(struct uart_port *port)
{
	unsigned int usr;

	usr = vt8500_read(port, VT8500_URUSR);
	if (usr & (1 << 4))
		return TIOCM_CTS;
	else
		return 0;
}