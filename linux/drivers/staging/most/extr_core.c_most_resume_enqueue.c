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
struct most_interface {TYPE_1__* p; } ;
struct most_channel {int enqueue_halt; int /*<<< orphan*/  hdm_fifo_wq; int /*<<< orphan*/  nq_mutex; } ;
struct TYPE_2__ {struct most_channel** channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void most_resume_enqueue(struct most_interface *iface, int id)
{
	struct most_channel *c = iface->p->channel[id];

	if (!c)
		return;

	mutex_lock(&c->nq_mutex);
	c->enqueue_halt = false;
	mutex_unlock(&c->nq_mutex);

	wake_up_interruptible(&c->hdm_fifo_wq);
}