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
struct uart_port {int regshift; int iotype; int /*<<< orphan*/  (* serial_out ) (struct uart_port*,int,int) ;int /*<<< orphan*/  iobase; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
#define  UPIO_AU 133 
#define  UPIO_MEM 132 
#define  UPIO_MEM16 131 
#define  UPIO_MEM32 130 
#define  UPIO_MEM32BE 129 
#define  UPIO_PORT 128 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int,int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial8250_early_out(struct uart_port *port, int offset, int value)
{
	int reg_offset = offset;
	offset <<= port->regshift;

	switch (port->iotype) {
	case UPIO_MEM:
		writeb(value, port->membase + offset);
		break;
	case UPIO_MEM16:
		writew(value, port->membase + offset);
		break;
	case UPIO_MEM32:
		writel(value, port->membase + offset);
		break;
	case UPIO_MEM32BE:
		iowrite32be(value, port->membase + offset);
		break;
	case UPIO_PORT:
		outb(value, port->iobase + offset);
		break;
	case UPIO_AU:
		port->serial_out(port, reg_offset, value);
		break;
	}
}