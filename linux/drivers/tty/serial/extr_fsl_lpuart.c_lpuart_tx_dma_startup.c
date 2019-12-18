#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ membase; } ;
struct lpuart_port {int lpuart_dma_tx_use; TYPE_1__ port; int /*<<< orphan*/  dma_wait; scalar_t__ dma_tx_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTBAUD ; 
 int UARTBAUD_TDMAE ; 
 scalar_t__ UARTCR5 ; 
 int UARTCR5_TDMAS ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int lpuart32_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_write (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_dma_tx_request (TYPE_1__*) ; 
 scalar_t__ lpuart_is_32 (struct lpuart_port*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void lpuart_tx_dma_startup(struct lpuart_port *sport)
{
	u32 uartbaud;

	if (sport->dma_tx_chan && !lpuart_dma_tx_request(&sport->port)) {
		init_waitqueue_head(&sport->dma_wait);
		sport->lpuart_dma_tx_use = true;
		if (lpuart_is_32(sport)) {
			uartbaud = lpuart32_read(&sport->port, UARTBAUD);
			lpuart32_write(&sport->port,
				       uartbaud | UARTBAUD_TDMAE, UARTBAUD);
		} else {
			writeb(readb(sport->port.membase + UARTCR5) |
				UARTCR5_TDMAS, sport->port.membase + UARTCR5);
		}
	} else {
		sport->lpuart_dma_tx_use = false;
	}
}