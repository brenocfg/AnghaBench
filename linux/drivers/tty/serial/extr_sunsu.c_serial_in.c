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
struct TYPE_2__ {int regshift; int iotype; int /*<<< orphan*/  iobase; int /*<<< orphan*/  membase; int /*<<< orphan*/  hub6; } ;
struct uart_sunsu_port {TYPE_1__ port; } ;

/* Variables and functions */
#define  UPIO_HUB6 129 
#define  UPIO_MEM 128 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int serial_in(struct uart_sunsu_port *up, int offset)
{
	offset <<= up->port.regshift;

	switch (up->port.iotype) {
	case UPIO_HUB6:
		outb(up->port.hub6 - 1 + offset, up->port.iobase);
		return inb(up->port.iobase + 1);

	case UPIO_MEM:
		return readb(up->port.membase + offset);

	default:
		return inb(up->port.iobase + offset);
	}
}