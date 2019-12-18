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
struct TYPE_3__ {int /*<<< orphan*/  delay_rts_after_send; } ;
struct TYPE_4__ {TYPE_1__ rs485; } ;
struct uart_8250_port {TYPE_2__ port; struct uart_8250_em485* em485; } ;
struct uart_8250_em485 {int /*<<< orphan*/  stop_tx_timer; int /*<<< orphan*/ * active_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __do_stop_tx_rs485 (struct uart_8250_port*) ; 
 int /*<<< orphan*/  start_hrtimer_ms (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __stop_tx_rs485(struct uart_8250_port *p)
{
	struct uart_8250_em485 *em485 = p->em485;

	/*
	 * __do_stop_tx_rs485 is going to set RTS according to config
	 * AND flush RX FIFO if required.
	 */
	if (p->port.rs485.delay_rts_after_send > 0) {
		em485->active_timer = &em485->stop_tx_timer;
		start_hrtimer_ms(&em485->stop_tx_timer,
				   p->port.rs485.delay_rts_after_send);
	} else {
		__do_stop_tx_rs485(p);
	}
}