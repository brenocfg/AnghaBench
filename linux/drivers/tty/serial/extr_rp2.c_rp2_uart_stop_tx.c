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
 int /*<<< orphan*/  RP2_TXRX_CTL ; 
 int /*<<< orphan*/  RP2_TXRX_CTL_TXIRQ_m ; 
 int /*<<< orphan*/  port_to_up (struct uart_port*) ; 
 int /*<<< orphan*/  rp2_rmw_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rp2_uart_stop_tx(struct uart_port *port)
{
	rp2_rmw_clr(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_TXIRQ_m);
}