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
struct uart_port {scalar_t__ irq; int uartclk; unsigned long mapbase; scalar_t__ iobase; } ;
struct serial_struct {scalar_t__ type; scalar_t__ irq; scalar_t__ io_type; int baud_base; scalar_t__ port; scalar_t__ hub6; scalar_t__ iomem_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PORT_ATMEL ; 
 scalar_t__ PORT_UNKNOWN ; 
 scalar_t__ SERIAL_IO_MEM ; 

__attribute__((used)) static int atmel_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	int ret = 0;
	if (ser->type != PORT_UNKNOWN && ser->type != PORT_ATMEL)
		ret = -EINVAL;
	if (port->irq != ser->irq)
		ret = -EINVAL;
	if (ser->io_type != SERIAL_IO_MEM)
		ret = -EINVAL;
	if (port->uartclk / 16 != ser->baud_base)
		ret = -EINVAL;
	if (port->mapbase != (unsigned long)ser->iomem_base)
		ret = -EINVAL;
	if (port->iobase != ser->port)
		ret = -EINVAL;
	if (ser->hub6 != 0)
		ret = -EINVAL;
	return ret;
}