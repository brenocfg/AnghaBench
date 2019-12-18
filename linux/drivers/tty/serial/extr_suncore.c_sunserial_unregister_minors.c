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
struct uart_driver {int nr; } ;

/* Variables and functions */
 int sunserial_current_minor ; 
 int /*<<< orphan*/  uart_unregister_driver (struct uart_driver*) ; 

void sunserial_unregister_minors(struct uart_driver *drv, int count)
{
	drv->nr -= count;
	sunserial_current_minor -= count;

	if (drv->nr == 0)
		uart_unregister_driver(drv);
}