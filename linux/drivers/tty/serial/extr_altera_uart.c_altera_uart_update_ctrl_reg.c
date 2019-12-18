#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct altera_uart {unsigned short imr; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_UART_CONTROL_REG ; 
 unsigned short ALTERA_UART_CONTROL_RTS_MSK ; 
 unsigned short ALTERA_UART_CONTROL_TRBK_MSK ; 
 int /*<<< orphan*/  altera_uart_writel (TYPE_1__*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_uart_update_ctrl_reg(struct altera_uart *pp)
{
	unsigned short imr = pp->imr;

	/*
	 * If the device doesn't have an irq, ensure that the irq bits are
	 * masked out to keep the irq line inactive.
	 */
	if (!pp->port.irq)
		imr &= ALTERA_UART_CONTROL_TRBK_MSK | ALTERA_UART_CONTROL_RTS_MSK;

	altera_uart_writel(&pp->port, imr, ALTERA_UART_CONTROL_REG);
}