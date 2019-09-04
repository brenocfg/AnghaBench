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
struct nvkm_notify {TYPE_1__* event; scalar_t__ data; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_notify_put (struct nvkm_notify*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nvkm_notify_fini(struct nvkm_notify *notify)
{
	unsigned long flags;
	if (notify->event) {
		nvkm_notify_put(notify);
		spin_lock_irqsave(&notify->event->list_lock, flags);
		list_del(&notify->head);
		spin_unlock_irqrestore(&notify->event->list_lock, flags);
		kfree((void *)notify->data);
		notify->event = NULL;
	}
}