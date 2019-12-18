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
 unsigned int TIOCM_RTS ; 
 unsigned int VT8500_RTS ; 
 int /*<<< orphan*/  VT8500_URLCR ; 
 unsigned int vt8500_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt8500_write (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vt8500_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	unsigned int lcr = vt8500_read(port, VT8500_URLCR);

	if (mctrl & TIOCM_RTS)
		lcr |= VT8500_RTS;
	else
		lcr &= ~VT8500_RTS;

	vt8500_write(port, lcr, VT8500_URLCR);
}