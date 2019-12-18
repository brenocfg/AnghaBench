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
typedef  int /*<<< orphan*/  u_int ;
struct ltq_uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  port; } ;
struct console {size_t index; } ;

/* Variables and functions */
 size_t MAXPORTS ; 
 struct ltq_uart_port** lqasc_port ; 
 int /*<<< orphan*/  lqasc_serial_port_write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lqasc_console_write(struct console *co, const char *s, u_int count)
{
	struct ltq_uart_port *ltq_port;
	unsigned long flags;

	if (co->index >= MAXPORTS)
		return;

	ltq_port = lqasc_port[co->index];
	if (!ltq_port)
		return;

	spin_lock_irqsave(&ltq_port->lock, flags);
	lqasc_serial_port_write(&ltq_port->port, s, count);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
}