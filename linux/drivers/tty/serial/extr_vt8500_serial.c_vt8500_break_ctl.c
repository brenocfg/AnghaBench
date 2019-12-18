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
 int VT8500_BREAK ; 
 int /*<<< orphan*/  VT8500_URLCR ; 
 int vt8500_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt8500_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vt8500_break_ctl(struct uart_port *port, int break_ctl)
{
	if (break_ctl)
		vt8500_write(port,
			     vt8500_read(port, VT8500_URLCR) | VT8500_BREAK,
			     VT8500_URLCR);
}