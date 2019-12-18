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
struct lpuart_port {int /*<<< orphan*/  port; int /*<<< orphan*/  lpuart_dma_tx_use; scalar_t__ lpuart_dma_rx_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTCTRL ; 
 unsigned long UARTCTRL_RIE ; 
 unsigned long UARTCTRL_TIE ; 
 int /*<<< orphan*/  UARTWATER ; 
 unsigned long UARTWATER_RXWATER_OFF ; 
 unsigned long UARTWATER_WATER_MASK ; 
 unsigned long lpuart32_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_write (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpuart32_configure(struct lpuart_port *sport)
{
	unsigned long temp;

	if (sport->lpuart_dma_rx_use) {
		/* RXWATER must be 0 */
		temp = lpuart32_read(&sport->port, UARTWATER);
		temp &= ~(UARTWATER_WATER_MASK << UARTWATER_RXWATER_OFF);
		lpuart32_write(&sport->port, temp, UARTWATER);
	}
	temp = lpuart32_read(&sport->port, UARTCTRL);
	if (!sport->lpuart_dma_rx_use)
		temp |= UARTCTRL_RIE;
	if (!sport->lpuart_dma_tx_use)
		temp |= UARTCTRL_TIE;
	lpuart32_write(&sport->port, temp, UARTCTRL);
}