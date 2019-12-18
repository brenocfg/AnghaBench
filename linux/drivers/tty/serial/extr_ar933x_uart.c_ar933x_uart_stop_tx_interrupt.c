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
struct ar933x_uart_port {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_INT_EN_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_TX_EMPTY ; 
 int /*<<< orphan*/  ar933x_uart_write (struct ar933x_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ar933x_uart_stop_tx_interrupt(struct ar933x_uart_port *up)
{
	up->ier &= ~AR933X_UART_INT_TX_EMPTY;
	ar933x_uart_write(up, AR933X_UART_INT_EN_REG, up->ier);
}