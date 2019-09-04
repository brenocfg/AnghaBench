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
struct IsdnCardState {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_ISR_PASS_LIMIT ; 
 int /*<<< orphan*/  UART_IIR ; 
 int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_DR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  receive_chars (struct IsdnCardState*,int*) ; 
 int serial_inp (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transmit_chars (struct IsdnCardState*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_interrupt_elsa(struct IsdnCardState *cs)
{
	int status, iir, msr;
	int pass_counter = 0;

#ifdef SERIAL_DEBUG_INTR
	printk(KERN_DEBUG "rs_interrupt_single(%d)...", cs->irq);
#endif

	do {
		status = serial_inp(cs, UART_LSR);
		debugl1(cs, "rs LSR %02x", status);
#ifdef SERIAL_DEBUG_INTR
		printk("status = %x...", status);
#endif
		if (status & UART_LSR_DR)
			receive_chars(cs, &status);
		if (status & UART_LSR_THRE)
			transmit_chars(cs, NULL);
		if (pass_counter++ > RS_ISR_PASS_LIMIT) {
			printk("rs_single loop break.\n");
			break;
		}
		iir = serial_inp(cs, UART_IIR);
		debugl1(cs, "rs IIR %02x", iir);
		if ((iir & 0xf) == 0) {
			msr = serial_inp(cs, UART_MSR);
			debugl1(cs, "rs MSR %02x", msr);
		}
	} while (!(iir & UART_IIR_NO_INT));
#ifdef SERIAL_DEBUG_INTR
	printk("end.\n");
#endif
}