#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ delay_rts_before_send; } ;
struct uart_port {TYPE_1__ rs485; } ;
struct kthread_work {int dummy; } ;
struct TYPE_4__ {struct uart_port port; } ;

/* Variables and functions */
 int SER_RS485_ENABLED ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  sc16is7xx_handle_tx (struct uart_port*) ; 
 TYPE_2__* to_sc16is7xx_one (struct kthread_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_work ; 

__attribute__((used)) static void sc16is7xx_tx_proc(struct kthread_work *ws)
{
	struct uart_port *port = &(to_sc16is7xx_one(ws, tx_work)->port);

	if ((port->rs485.flags & SER_RS485_ENABLED) &&
	    (port->rs485.delay_rts_before_send > 0))
		msleep(port->rs485.delay_rts_before_send);

	sc16is7xx_handle_tx(port);
}