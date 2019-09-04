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
struct nvkm_notify {int /*<<< orphan*/  flags; struct nvkm_event* event; } ;
struct nvkm_event {int /*<<< orphan*/  refs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_NOTIFY_USER ; 
 scalar_t__ likely (struct nvkm_event*) ; 
 int /*<<< orphan*/  nvkm_notify_get_locked (struct nvkm_notify*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nvkm_notify_get(struct nvkm_notify *notify)
{
	struct nvkm_event *event = notify->event;
	unsigned long flags;
	if (likely(event) &&
	    !test_and_set_bit(NVKM_NOTIFY_USER, &notify->flags)) {
		spin_lock_irqsave(&event->refs_lock, flags);
		nvkm_notify_get_locked(notify);
		spin_unlock_irqrestore(&event->refs_lock, flags);
	}
}