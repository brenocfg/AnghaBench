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
struct visornic_devdata {int /*<<< orphan*/  irq_poll_timer; int /*<<< orphan*/  interrupt_rcvd; int /*<<< orphan*/  napi; TYPE_1__* dev; } ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  visorchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCHAN_FROM_IOPART ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct visornic_devdata* devdata ; 
 struct visornic_devdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_poll_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visorchannel_signalempty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_for_irq(struct timer_list *t)
{
	struct visornic_devdata *devdata = from_timer(devdata, t,
						      irq_poll_timer);

	if (!visorchannel_signalempty(
				   devdata->dev->visorchannel,
				   IOCHAN_FROM_IOPART))
		napi_schedule(&devdata->napi);

	atomic_set(&devdata->interrupt_rcvd, 0);

	mod_timer(&devdata->irq_poll_timer, msecs_to_jiffies(2));
}