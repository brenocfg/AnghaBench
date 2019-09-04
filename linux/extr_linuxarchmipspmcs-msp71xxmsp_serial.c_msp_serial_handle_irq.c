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
struct uart_port {int regshift; scalar_t__ membase; struct msp_uart_data* private_data; } ;
struct msp_uart_data {int /*<<< orphan*/  last_lcr; } ;

/* Variables and functions */
 int UART_IIR ; 
 unsigned int UART_IIR_BUSY ; 
 int UART_LCR ; 
 unsigned int readb (scalar_t__) ; 
 scalar_t__ serial8250_handle_irq (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int msp_serial_handle_irq(struct uart_port *p)
{
	struct msp_uart_data *d = p->private_data;
	unsigned int iir = readb(p->membase + (UART_IIR << p->regshift));

	if (serial8250_handle_irq(p, iir)) {
		return 1;
	} else if ((iir & UART_IIR_BUSY) == UART_IIR_BUSY) {
		/*
		 * The DesignWare APB UART has an Busy Detect (0x07) interrupt
		 * meaning an LCR write attempt occurred while the UART was
		 * busy. The interrupt must be cleared by reading the UART
		 * status register (USR) and the LCR re-written.
		 *
		 * Note: MSP reserves 0x20 bytes of address space for the UART
		 * and the USR is mapped in a separate block at an offset of
		 * 0xc0 from the start of the UART.
		 */
		(void)readb(p->membase + 0xc0);
		writeb(d->last_lcr, p->membase + (UART_LCR << p->regshift));

		return 1;
	}

	return 0;
}