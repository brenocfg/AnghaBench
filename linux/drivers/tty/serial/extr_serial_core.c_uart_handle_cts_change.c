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
struct TYPE_3__ {int /*<<< orphan*/  cts; } ;
struct uart_port {int hw_stopped; TYPE_2__* ops; TYPE_1__ icount; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop_tx ) (struct uart_port*) ;int /*<<< orphan*/  (* start_tx ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*) ; 
 scalar_t__ uart_softcts_mode (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

void uart_handle_cts_change(struct uart_port *uport, unsigned int status)
{
	lockdep_assert_held_once(&uport->lock);

	uport->icount.cts++;

	if (uart_softcts_mode(uport)) {
		if (uport->hw_stopped) {
			if (status) {
				uport->hw_stopped = 0;
				uport->ops->start_tx(uport);
				uart_write_wakeup(uport);
			}
		} else {
			if (!status) {
				uport->hw_stopped = 1;
				uport->ops->stop_tx(uport);
			}
		}

	}
}