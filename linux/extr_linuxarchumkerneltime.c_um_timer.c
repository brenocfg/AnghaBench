#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_13__ {TYPE_4__* mm; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* event_handler ) (TYPE_5__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  pid; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_10__ {TYPE_2__ id; } ;
struct TYPE_11__ {TYPE_3__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_7__* get_current () ; 
 int /*<<< orphan*/  os_alarm_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 TYPE_5__ timer_clockevent ; 

__attribute__((used)) static irqreturn_t um_timer(int irq, void *dev)
{
	if (get_current()->mm != NULL)
	{
        /* userspace - relay signal, results in correct userspace timers */
		os_alarm_process(get_current()->mm->context.id.u.pid);
	}

	(*timer_clockevent.event_handler)(&timer_clockevent);

	return IRQ_HANDLED;
}