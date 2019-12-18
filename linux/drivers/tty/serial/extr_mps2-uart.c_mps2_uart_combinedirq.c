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
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ mps2_uart_oerrirq (int,void*) ; 
 scalar_t__ mps2_uart_rxirq (int,void*) ; 
 scalar_t__ mps2_uart_txirq (int,void*) ; 

__attribute__((used)) static irqreturn_t mps2_uart_combinedirq(int irq, void *data)
{
	if (mps2_uart_rxirq(irq, data) == IRQ_HANDLED)
		return IRQ_HANDLED;

	if (mps2_uart_txirq(irq, data) == IRQ_HANDLED)
		return IRQ_HANDLED;

	if (mps2_uart_oerrirq(irq, data) == IRQ_HANDLED)
		return IRQ_HANDLED;

	return IRQ_NONE;
}