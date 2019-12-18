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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDA_UART_CMD_SET ; 
 int /*<<< orphan*/  RDA_UART_IRQ_MASK ; 
 int /*<<< orphan*/  RDA_UART_TX_DATA_NEEDED ; 
 int /*<<< orphan*/  RDA_UART_TX_FIFO_RESET ; 
 int /*<<< orphan*/  rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rda_uart_stop_tx(struct uart_port *port)
{
	u32 val;

	val = rda_uart_read(port, RDA_UART_IRQ_MASK);
	val &= ~RDA_UART_TX_DATA_NEEDED;
	rda_uart_write(port, val, RDA_UART_IRQ_MASK);

	val = rda_uart_read(port, RDA_UART_CMD_SET);
	val |= RDA_UART_TX_FIFO_RESET;
	rda_uart_write(port, val, RDA_UART_CMD_SET);
}