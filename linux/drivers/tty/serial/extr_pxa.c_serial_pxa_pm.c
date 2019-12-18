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
struct uart_pxa_port {int /*<<< orphan*/  clk; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
serial_pxa_pm(struct uart_port *port, unsigned int state,
	      unsigned int oldstate)
{
	struct uart_pxa_port *up = (struct uart_pxa_port *)port;

	if (!state)
		clk_prepare_enable(up->clk);
	else
		clk_disable_unprepare(up->clk);
}