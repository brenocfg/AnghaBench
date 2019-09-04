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
struct nvkm_notify {int (* func ) (struct nvkm_notify*) ;int /*<<< orphan*/  flags; struct nvkm_event* event; } ;
struct nvkm_event {int /*<<< orphan*/  refs_lock; } ;

/* Variables and functions */
 int NVKM_NOTIFY_KEEP ; 
 int /*<<< orphan*/  NVKM_NOTIFY_USER ; 
 int /*<<< orphan*/  nvkm_notify_get_locked (struct nvkm_notify*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct nvkm_notify*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
nvkm_notify_func(struct nvkm_notify *notify)
{
	struct nvkm_event *event = notify->event;
	int ret = notify->func(notify);
	unsigned long flags;
	if ((ret == NVKM_NOTIFY_KEEP) ||
	    !test_and_clear_bit(NVKM_NOTIFY_USER, &notify->flags)) {
		spin_lock_irqsave(&event->refs_lock, flags);
		nvkm_notify_get_locked(notify);
		spin_unlock_irqrestore(&event->refs_lock, flags);
	}
}