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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ serial8250_clear_THRI (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put_tx (struct uart_8250_port*) ; 

__attribute__((used)) static inline void __do_stop_tx(struct uart_8250_port *p)
{
	if (serial8250_clear_THRI(p))
		serial8250_rpm_put_tx(p);
}