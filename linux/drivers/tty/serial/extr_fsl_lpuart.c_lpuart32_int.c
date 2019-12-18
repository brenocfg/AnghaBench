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
struct lpuart_port {int /*<<< orphan*/  port; int /*<<< orphan*/  lpuart_dma_tx_use; int /*<<< orphan*/  lpuart_dma_rx_use; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UARTSTAT ; 
 unsigned long UARTSTAT_RDRF ; 
 unsigned long UARTSTAT_TDRE ; 
 int /*<<< orphan*/  UARTWATER ; 
 unsigned long UARTWATER_RXCNT_OFF ; 
 unsigned long lpuart32_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_rxint (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart32_txint (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart32_write (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lpuart32_int(int irq, void *dev_id)
{
	struct lpuart_port *sport = dev_id;
	unsigned long sts, rxcount;

	sts = lpuart32_read(&sport->port, UARTSTAT);
	rxcount = lpuart32_read(&sport->port, UARTWATER);
	rxcount = rxcount >> UARTWATER_RXCNT_OFF;

	if ((sts & UARTSTAT_RDRF || rxcount > 0) && !sport->lpuart_dma_rx_use)
		lpuart32_rxint(sport);

	if ((sts & UARTSTAT_TDRE) && !sport->lpuart_dma_tx_use)
		lpuart32_txint(sport);

	lpuart32_write(&sport->port, sts, UARTSTAT);
	return IRQ_HANDLED;
}