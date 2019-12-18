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
typedef  scalar_t__ u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_notify {scalar_t__ size; int block; int (* func ) (struct nvkm_notify*) ;struct nvkm_event* event; int /*<<< orphan*/  head; int /*<<< orphan*/ * data; scalar_t__ flags; int /*<<< orphan*/  work; } ;
struct nvkm_event {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; TYPE_1__* func; int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int (* ctor ) (struct nvkm_object*,void*,scalar_t__,struct nvkm_notify*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVKM_NOTIFY_WORK ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_notify_work ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct nvkm_object*,void*,scalar_t__,struct nvkm_notify*) ; 

int
nvkm_notify_init(struct nvkm_object *object, struct nvkm_event *event,
		 int (*func)(struct nvkm_notify *), bool work,
		 void *data, u32 size, u32 reply,
		 struct nvkm_notify *notify)
{
	unsigned long flags;
	int ret = -ENODEV;
	if ((notify->event = event), event->refs) {
		ret = event->func->ctor(object, data, size, notify);
		if (ret == 0 && (ret = -EINVAL, notify->size == reply)) {
			notify->flags = 0;
			notify->block = 1;
			notify->func = func;
			notify->data = NULL;
			if (ret = 0, work) {
				INIT_WORK(&notify->work, nvkm_notify_work);
				set_bit(NVKM_NOTIFY_WORK, &notify->flags);
				notify->data = kmalloc(reply, GFP_KERNEL);
				if (!notify->data)
					ret = -ENOMEM;
			}
		}
		if (ret == 0) {
			spin_lock_irqsave(&event->list_lock, flags);
			list_add_tail(&notify->head, &event->list);
			spin_unlock_irqrestore(&event->list_lock, flags);
		}
	}
	if (ret)
		notify->event = NULL;
	return ret;
}