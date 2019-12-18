#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usif_notify {int reply; scalar_t__ route; int /*<<< orphan*/  enabled; TYPE_5__* p; scalar_t__ token; } ;
struct nvif_notify_rep_v0 {int version; scalar_t__ route; scalar_t__ token; } ;
struct drm_file {scalar_t__ event_space; int /*<<< orphan*/  event_wait; int /*<<< orphan*/  event_list; TYPE_1__* minor; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_9__ {TYPE_3__ base; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; struct drm_file* file_priv; } ;
struct TYPE_10__ {TYPE_4__ e; TYPE_2__ base; } ;
struct TYPE_6__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NVDRM_NOTIFY_USIF ; 
 int NVIF_NOTIFY_DROP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int
usif_notify(const void *header, u32 length, const void *data, u32 size)
{
	struct usif_notify *ntfy = NULL;
	const union {
		struct nvif_notify_rep_v0 v0;
	} *rep = header;
	struct drm_device *dev;
	struct drm_file *filp;
	unsigned long flags;

	if (length == sizeof(rep->v0) && rep->v0.version == 0) {
		if (WARN_ON(!(ntfy = (void *)(unsigned long)rep->v0.token)))
			return NVIF_NOTIFY_DROP;
		BUG_ON(rep->v0.route != NVDRM_NOTIFY_USIF);
	} else
	if (WARN_ON(1))
		return NVIF_NOTIFY_DROP;

	if (WARN_ON(!ntfy->p || ntfy->reply != (length + size)))
		return NVIF_NOTIFY_DROP;
	filp = ntfy->p->base.file_priv;
	dev = filp->minor->dev;

	memcpy(&ntfy->p->e.data[0], header, length);
	memcpy(&ntfy->p->e.data[length], data, size);
	switch (rep->v0.version) {
	case 0: {
		struct nvif_notify_rep_v0 *rep = (void *)ntfy->p->e.data;
		rep->route = ntfy->route;
		rep->token = ntfy->token;
	}
		break;
	default:
		BUG();
		break;
	}

	spin_lock_irqsave(&dev->event_lock, flags);
	if (!WARN_ON(filp->event_space < ntfy->p->e.base.length)) {
		list_add_tail(&ntfy->p->base.link, &filp->event_list);
		filp->event_space -= ntfy->p->e.base.length;
	}
	wake_up_interruptible(&filp->event_wait);
	spin_unlock_irqrestore(&dev->event_lock, flags);
	atomic_set(&ntfy->enabled, 0);
	return NVIF_NOTIFY_DROP;
}