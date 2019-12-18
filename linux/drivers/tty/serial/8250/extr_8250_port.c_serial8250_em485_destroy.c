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
struct uart_8250_port {TYPE_1__* em485; } ;
struct TYPE_2__ {int /*<<< orphan*/  stop_tx_timer; int /*<<< orphan*/  start_tx_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void serial8250_em485_destroy(struct uart_8250_port *p)
{
	if (!p->em485)
		return;

	hrtimer_cancel(&p->em485->start_tx_timer);
	hrtimer_cancel(&p->em485->stop_tx_timer);

	kfree(p->em485);
	p->em485 = NULL;
}