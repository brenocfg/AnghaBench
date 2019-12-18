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
 unsigned char inb (unsigned long) ; 
 int /*<<< orphan*/  outb (unsigned short,unsigned long) ; 
 int /*<<< orphan*/  port_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char indirect_read(struct pd6729_socket *socket,
				   unsigned short reg)
{
	unsigned long port;
	unsigned char val;
	unsigned long flags;

	spin_lock_irqsave(&port_lock, flags);
	reg += socket->number * 0x40;
	port = socket->io_base;
	outb(reg, port);
	val = inb(port + 1);
	spin_unlock_irqrestore(&port_lock, flags);

	return val;
}