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
struct sm501_devdata {int /*<<< orphan*/  irq; TYPE_1__* io_res; scalar_t__ regs; } ;
struct plat_serial8250_port {int flags; int regshift; int uartclk; int /*<<< orphan*/  irq; int /*<<< orphan*/  iotype; scalar_t__ mapbase; scalar_t__ membase; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int UPF_BOOT_AUTOCONF ; 
 int UPF_SHARE_IRQ ; 
 int UPF_SKIP_TEST ; 
 int /*<<< orphan*/  UPIO_MEM ; 

__attribute__((used)) static void sm501_setup_uart_data(struct sm501_devdata *sm,
				  struct plat_serial8250_port *uart_data,
				  unsigned int offset)
{
	uart_data->membase = sm->regs + offset;
	uart_data->mapbase = sm->io_res->start + offset;
	uart_data->iotype = UPIO_MEM;
	uart_data->irq = sm->irq;
	uart_data->flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_SHARE_IRQ;
	uart_data->regshift = 2;
	uart_data->uartclk = (9600 * 16);
}