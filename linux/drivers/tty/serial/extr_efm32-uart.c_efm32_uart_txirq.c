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
typedef  int u32 ;
struct efm32_uart_port {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  UARTn_IF ; 
 int /*<<< orphan*/  UARTn_IFC ; 
 int UARTn_IF_TXBL ; 
 int UARTn_IF_TXC ; 
 int efm32_uart_read32 (struct efm32_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_uart_tx_chars (struct efm32_uart_port*) ; 
 int /*<<< orphan*/  efm32_uart_write32 (struct efm32_uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t efm32_uart_txirq(int irq, void *data)
{
	struct efm32_uart_port *efm_port = data;
	u32 irqflag = efm32_uart_read32(efm_port, UARTn_IF);

	/* TXBL doesn't need to be cleared */
	if (irqflag & UARTn_IF_TXC)
		efm32_uart_write32(efm_port, UARTn_IF_TXC, UARTn_IFC);

	if (irqflag & (UARTn_IF_TXC | UARTn_IF_TXBL)) {
		efm32_uart_tx_chars(efm_port);
		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}