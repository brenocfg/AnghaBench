#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int MCR; scalar_t__ IER; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  UART_RX ; 
 int serial_inp (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_outp (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mshutdown(struct IsdnCardState *cs)
{

#ifdef SERIAL_DEBUG_OPEN
	printk(KERN_DEBUG"Shutting down serial ....");
#endif

	/*
	 * clear delta_msr_wait queue to avoid mem leaks: we may free the irq
	 * here so the queue might never be waken up
	 */

	cs->hw.elsa.IER = 0;
	serial_outp(cs, UART_IER, 0x00);	/* disable all intrs */
	cs->hw.elsa.MCR &= ~UART_MCR_OUT2;

	/* disable break condition */
	serial_outp(cs, UART_LCR, serial_inp(cs, UART_LCR) & ~UART_LCR_SBC);

	cs->hw.elsa.MCR &= ~(UART_MCR_DTR | UART_MCR_RTS);
	serial_outp(cs, UART_MCR, cs->hw.elsa.MCR);

	/* disable FIFO's */
	serial_outp(cs, UART_FCR, (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT));
	serial_inp(cs, UART_RX);    /* read data port to reset things */

#ifdef SERIAL_DEBUG_OPEN
	printk(" done\n");
#endif
}