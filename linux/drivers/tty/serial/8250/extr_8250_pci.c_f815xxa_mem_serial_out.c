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
struct uart_port {scalar_t__ membase; struct f815xxa_data* private_data; } ;
struct f815xxa_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ UART_SCR ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void f815xxa_mem_serial_out(struct uart_port *p, int offset, int value)
{
	struct f815xxa_data *data = p->private_data;
	unsigned long flags;

	spin_lock_irqsave(&data->lock, flags);
	writeb(value, p->membase + offset);
	readb(p->membase + UART_SCR); /* Dummy read for flush pcie tx queue */
	spin_unlock_irqrestore(&data->lock, flags);
}