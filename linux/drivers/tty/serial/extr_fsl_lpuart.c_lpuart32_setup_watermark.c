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
struct lpuart_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTCTRL ; 
 unsigned long UARTCTRL_RE ; 
 unsigned long UARTCTRL_RIE ; 
 unsigned long UARTCTRL_TCIE ; 
 unsigned long UARTCTRL_TE ; 
 unsigned long UARTCTRL_TIE ; 
 int /*<<< orphan*/  UARTFIFO ; 
 unsigned long UARTFIFO_RXFE ; 
 unsigned long UARTFIFO_RXFLUSH ; 
 unsigned long UARTFIFO_TXFE ; 
 unsigned long UARTFIFO_TXFLUSH ; 
 int /*<<< orphan*/  UARTWATER ; 
 int UARTWATER_RXWATER_OFF ; 
 int UARTWATER_TXWATER_OFF ; 
 unsigned long lpuart32_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_write (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpuart32_setup_watermark(struct lpuart_port *sport)
{
	unsigned long val, ctrl;
	unsigned long ctrl_saved;

	ctrl = lpuart32_read(&sport->port, UARTCTRL);
	ctrl_saved = ctrl;
	ctrl &= ~(UARTCTRL_TIE | UARTCTRL_TCIE | UARTCTRL_TE |
			UARTCTRL_RIE | UARTCTRL_RE);
	lpuart32_write(&sport->port, ctrl, UARTCTRL);

	/* enable FIFO mode */
	val = lpuart32_read(&sport->port, UARTFIFO);
	val |= UARTFIFO_TXFE | UARTFIFO_RXFE;
	val |= UARTFIFO_TXFLUSH | UARTFIFO_RXFLUSH;
	lpuart32_write(&sport->port, val, UARTFIFO);

	/* set the watermark */
	val = (0x1 << UARTWATER_RXWATER_OFF) | (0x0 << UARTWATER_TXWATER_OFF);
	lpuart32_write(&sport->port, val, UARTWATER);

	/* Restore cr2 */
	lpuart32_write(&sport->port, ctrl_saved, UARTCTRL);
}