#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_notify {scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/  work; int /*<<< orphan*/  flags; scalar_t__ block; struct nvkm_event* event; } ;
struct nvkm_event {int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NVKM_NOTIFY_WORK ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_notify_func (struct nvkm_notify*) ; 
 int /*<<< orphan*/  nvkm_notify_put_locked (struct nvkm_notify*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nvkm_notify_send(struct nvkm_notify *notify, void *data, u32 size)
{
	struct nvkm_event *event = notify->event;
	unsigned long flags;

	assert_spin_locked(&event->list_lock);
	BUG_ON(size != notify->size);

	spin_lock_irqsave(&event->refs_lock, flags);
	if (notify->block) {
		spin_unlock_irqrestore(&event->refs_lock, flags);
		return;
	}
	nvkm_notify_put_locked(notify);
	spin_unlock_irqrestore(&event->refs_lock, flags);

	if (test_bit(NVKM_NOTIFY_WORK, &notify->flags)) {
		memcpy((void *)notify->data, data, size);
		schedule_work(&notify->work);
	} else {
		notify->data = data;
		nvkm_notify_func(notify);
		notify->data = NULL;
	}
}