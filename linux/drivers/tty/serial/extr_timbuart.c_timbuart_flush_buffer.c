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
typedef  int u8 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ TIMBUART_CTRL ; 
 int TIMBUART_CTRL_FLSHTX ; 
 scalar_t__ TIMBUART_ISR ; 
 int /*<<< orphan*/  TXBF ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  timbuart_tx_empty (struct uart_port*) ; 

__attribute__((used)) static void timbuart_flush_buffer(struct uart_port *port)
{
	if (!timbuart_tx_empty(port)) {
		u8 ctl = ioread8(port->membase + TIMBUART_CTRL) |
			TIMBUART_CTRL_FLSHTX;

		iowrite8(ctl, port->membase + TIMBUART_CTRL);
		iowrite32(TXBF, port->membase + TIMBUART_ISR);
	}
}