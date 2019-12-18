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
struct sc16is7xx_port {int /*<<< orphan*/  efr_lock; TYPE_1__* devtype; } ;
struct kthread_work {int dummy; } ;
struct TYPE_2__ {int nr_uart; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_work ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sc16is7xx_port_irq (struct sc16is7xx_port*,int) ; 
 struct sc16is7xx_port* to_sc16is7xx_port (struct kthread_work*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc16is7xx_ist(struct kthread_work *ws)
{
	struct sc16is7xx_port *s = to_sc16is7xx_port(ws, irq_work);

	mutex_lock(&s->efr_lock);

	while (1) {
		bool keep_polling = false;
		int i;

		for (i = 0; i < s->devtype->nr_uart; ++i)
			keep_polling |= sc16is7xx_port_irq(s, i);
		if (!keep_polling)
			break;
	}

	mutex_unlock(&s->efr_lock);
}