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
struct msp_uart_data {int last_lcr; } ;

/* Variables and functions */
 int UART_LCR ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void msp_serial_out(struct uart_port *p, int offset, int value)
{
	struct msp_uart_data *d = p->private_data;

	if (offset == UART_LCR)
		d->last_lcr = value;

	offset <<= p->regshift;
	writeb(value, p->membase + offset);
}