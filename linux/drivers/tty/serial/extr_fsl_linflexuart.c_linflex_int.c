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
struct uart_port {scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long LINFLEXD_UARTSR_DRFRFE ; 
 unsigned long LINFLEXD_UARTSR_DTFTFF ; 
 scalar_t__ UARTSR ; 
 int /*<<< orphan*/  linflex_rxint (int,void*) ; 
 int /*<<< orphan*/  linflex_txint (int,void*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t linflex_int(int irq, void *dev_id)
{
	struct uart_port *sport = dev_id;
	unsigned long status;

	status = readl(sport->membase + UARTSR);

	if (status & LINFLEXD_UARTSR_DRFRFE)
		linflex_rxint(irq, dev_id);
	if (status & LINFLEXD_UARTSR_DTFTFF)
		linflex_txint(irq, dev_id);

	return IRQ_HANDLED;
}