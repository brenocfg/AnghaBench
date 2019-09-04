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

/* Variables and functions */
 unsigned char DLAB ; 
 scalar_t__ DLH ; 
 scalar_t__ DLL ; 
 scalar_t__ FCR ; 
 scalar_t__ IER ; 
 scalar_t__ LCR ; 
 scalar_t__ MCR ; 
 int early_serial_base ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void early_serial_init(int port, int baud)
{
	unsigned char c;
	unsigned divisor;

	outb(0x3, port + LCR);	/* 8n1 */
	outb(0, port + IER);	/* no interrupt */
	outb(0, port + FCR);	/* no fifo */
	outb(0x3, port + MCR);	/* DTR + RTS */

	divisor	= 115200 / baud;
	c = inb(port + LCR);
	outb(c | DLAB, port + LCR);
	outb(divisor & 0xff, port + DLL);
	outb((divisor >> 8) & 0xff, port + DLH);
	outb(c & ~DLAB, port + LCR);

	early_serial_base = port;
}