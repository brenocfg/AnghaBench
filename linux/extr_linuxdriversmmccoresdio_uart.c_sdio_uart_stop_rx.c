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
struct sdio_uart_port {int /*<<< orphan*/  ier; int /*<<< orphan*/  read_status_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_LSR_DR ; 
 int /*<<< orphan*/  sdio_out (struct sdio_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdio_uart_stop_rx(struct sdio_uart_port *port)
{
	port->ier &= ~UART_IER_RLSI;
	port->read_status_mask &= ~UART_LSR_DR;
	sdio_out(port, UART_IER, port->ier);
}