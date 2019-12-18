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

/* Variables and functions */
 scalar_t__ LINCR1 ; 
 unsigned long LINFLEXD_LINCR1_BF ; 
 unsigned long LINFLEXD_LINCR1_INIT ; 
 unsigned long LINFLEXD_LINCR1_MME ; 
 unsigned long LINFLEXD_LINIER_DRIE ; 
 unsigned long LINFLEXD_LINIER_DTIE ; 
 unsigned long LINFLEXD_LINSR_LINS_INITMODE ; 
 unsigned long LINFLEXD_LINSR_LINS_MASK ; 
 unsigned long LINFLEXD_UARTCR_RXEN ; 
 unsigned long LINFLEXD_UARTCR_TXEN ; 
 unsigned long LINFLEXD_UARTCR_UART ; 
 unsigned long LINFLEXD_UARTCR_WL0 ; 
 scalar_t__ LINIER ; 
 scalar_t__ LINSR ; 
 scalar_t__ UARTCR ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void linflex_setup_watermark(struct uart_port *sport)
{
	unsigned long cr, ier, cr1;

	/* Disable transmission/reception */
	ier = readl(sport->membase + LINIER);
	ier &= ~(LINFLEXD_LINIER_DRIE | LINFLEXD_LINIER_DTIE);
	writel(ier, sport->membase + LINIER);

	cr = readl(sport->membase + UARTCR);
	cr &= ~(LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN);
	writel(cr, sport->membase + UARTCR);

	/* Enter initialization mode by setting INIT bit */

	/* set the Linflex in master mode and activate by-pass filter */
	cr1 = LINFLEXD_LINCR1_BF | LINFLEXD_LINCR1_MME
	      | LINFLEXD_LINCR1_INIT;
	writel(cr1, sport->membase + LINCR1);

	/* wait for init mode entry */
	while ((readl(sport->membase + LINSR)
		& LINFLEXD_LINSR_LINS_MASK)
		!= LINFLEXD_LINSR_LINS_INITMODE)
		;

	/*
	 *	UART = 0x1;		- Linflex working in UART mode
	 *	TXEN = 0x1;		- Enable transmission of data now
	 *	RXEn = 0x1;		- Receiver enabled
	 *	WL0 = 0x1;		- 8 bit data
	 *	PCE = 0x0;		- No parity
	 */

	/* set UART bit to allow writing other bits */
	writel(LINFLEXD_UARTCR_UART, sport->membase + UARTCR);

	cr = (LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN |
	      LINFLEXD_UARTCR_WL0 | LINFLEXD_UARTCR_UART);

	writel(cr, sport->membase + UARTCR);

	cr1 &= ~(LINFLEXD_LINCR1_INIT);

	writel(cr1, sport->membase + LINCR1);

	ier = readl(sport->membase + LINIER);
	ier |= LINFLEXD_LINIER_DRIE;
	ier |= LINFLEXD_LINIER_DTIE;

	writel(ier, sport->membase + LINIER);
}