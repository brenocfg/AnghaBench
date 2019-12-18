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
struct TYPE_2__ {scalar_t__ membase; } ;
struct lpuart_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UARTCFIFO ; 
 unsigned char UARTCFIFO_RXFLUSH ; 
 unsigned char UARTCFIFO_TXFLUSH ; 
 scalar_t__ UARTCR2 ; 
 unsigned char UARTCR2_RE ; 
 unsigned char UARTCR2_RIE ; 
 unsigned char UARTCR2_TCIE ; 
 unsigned char UARTCR2_TE ; 
 unsigned char UARTCR2_TIE ; 
 scalar_t__ UARTDR ; 
 scalar_t__ UARTPFIFO ; 
 unsigned char UARTPFIFO_RXFE ; 
 unsigned char UARTPFIFO_TXFE ; 
 scalar_t__ UARTRWFIFO ; 
 scalar_t__ UARTSFIFO ; 
 unsigned char UARTSFIFO_RXUF ; 
 scalar_t__ UARTSR1 ; 
 int UARTSR1_RDRF ; 
 scalar_t__ UARTTWFIFO ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void lpuart_setup_watermark(struct lpuart_port *sport)
{
	unsigned char val, cr2;
	unsigned char cr2_saved;

	cr2 = readb(sport->port.membase + UARTCR2);
	cr2_saved = cr2;
	cr2 &= ~(UARTCR2_TIE | UARTCR2_TCIE | UARTCR2_TE |
			UARTCR2_RIE | UARTCR2_RE);
	writeb(cr2, sport->port.membase + UARTCR2);

	val = readb(sport->port.membase + UARTPFIFO);
	writeb(val | UARTPFIFO_TXFE | UARTPFIFO_RXFE,
			sport->port.membase + UARTPFIFO);

	/* flush Tx and Rx FIFO */
	writeb(UARTCFIFO_TXFLUSH | UARTCFIFO_RXFLUSH,
			sport->port.membase + UARTCFIFO);

	/* explicitly clear RDRF */
	if (readb(sport->port.membase + UARTSR1) & UARTSR1_RDRF) {
		readb(sport->port.membase + UARTDR);
		writeb(UARTSFIFO_RXUF, sport->port.membase + UARTSFIFO);
	}

	writeb(0, sport->port.membase + UARTTWFIFO);
	writeb(1, sport->port.membase + UARTRWFIFO);

	/* Restore cr2 */
	writeb(cr2_saved, sport->port.membase + UARTCR2);
}