#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct parport {int /*<<< orphan*/  timer; TYPE_3__* physport; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {TYPE_1__ ieee1284; TYPE_2__* cad; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timeout_waiting_on_port ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int parport_wait_event (struct parport *port, signed long timeout)
{
	int ret;

	if (!port->physport->cad->timeout)
		/* Zero timeout is special, and we can't down() the
		   semaphore. */
		return 1;

	timer_setup(&port->timer, timeout_waiting_on_port, 0);
	mod_timer(&port->timer, jiffies + timeout);
	ret = down_interruptible (&port->physport->ieee1284.irq);
	if (!del_timer_sync(&port->timer) && !ret)
		/* Timed out. */
		ret = 1;

	return ret;
}