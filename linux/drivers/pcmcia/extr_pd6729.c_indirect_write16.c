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
struct pd6729_socket {int number; unsigned long io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned char,unsigned long) ; 
 int /*<<< orphan*/  port_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void indirect_write16(struct pd6729_socket *socket, unsigned short reg,
			     unsigned short value)
{
	unsigned long port;
	unsigned char val;
	unsigned long flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket->number * 0x40;
	port = socket->io_base;

	outb(reg, port);
	val = value & 255;
	outb(val, port + 1);

	reg++;

	outb(reg, port);
	val = value >> 8;
	outb(val, port + 1);
	spin_unlock_irqrestore(&port_lock, flags);
}