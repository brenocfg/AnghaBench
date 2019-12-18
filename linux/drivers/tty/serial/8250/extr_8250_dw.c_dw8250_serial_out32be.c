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
struct uart_port {int regshift; scalar_t__ membase; int /*<<< orphan*/  private_data; } ;
struct dw8250_data {int /*<<< orphan*/  uart_16550_compatible; } ;

/* Variables and functions */
 int UART_LCR ; 
 int /*<<< orphan*/  dw8250_check_lcr (struct uart_port*,int) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 struct dw8250_data* to_dw8250_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw8250_serial_out32be(struct uart_port *p, int offset, int value)
{
	struct dw8250_data *d = to_dw8250_data(p->private_data);

	iowrite32be(value, p->membase + (offset << p->regshift));

	if (offset == UART_LCR && !d->uart_16550_compatible)
		dw8250_check_lcr(p, value);
}