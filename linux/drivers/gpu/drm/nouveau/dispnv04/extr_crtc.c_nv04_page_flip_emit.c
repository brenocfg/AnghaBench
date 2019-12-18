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
struct nv04_page_flip_state {int /*<<< orphan*/  head; } ;
struct nouveau_fence_chan {int /*<<< orphan*/  flip; } ;
struct nouveau_fence {int dummy; } ;
struct nouveau_drm {struct drm_device* dev; } ;
struct nouveau_channel {struct nouveau_drm* drm; struct nouveau_fence_chan* fence; } ;
struct nouveau_bo {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NV_SW_PAGE_FLIP ; 
 int /*<<< orphan*/  NvSubSw ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int nouveau_fence_new (struct nouveau_channel*,int,struct nouveau_fence**) ; 
 int nouveau_fence_sync (struct nouveau_bo*,struct nouveau_channel*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nv04_page_flip_emit(struct nouveau_channel *chan,
		    struct nouveau_bo *old_bo,
		    struct nouveau_bo *new_bo,
		    struct nv04_page_flip_state *s,
		    struct nouveau_fence **pfence)
{
	struct nouveau_fence_chan *fctx = chan->fence;
	struct nouveau_drm *drm = chan->drm;
	struct drm_device *dev = drm->dev;
	unsigned long flags;
	int ret;

	/* Queue it to the pending list */
	spin_lock_irqsave(&dev->event_lock, flags);
	list_add_tail(&s->head, &fctx->flip);
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/* Synchronize with the old framebuffer */
	ret = nouveau_fence_sync(old_bo, chan, false, false);
	if (ret)
		goto fail;

	/* Emit the pageflip */
	ret = RING_SPACE(chan, 2);
	if (ret)
		goto fail;

	BEGIN_NV04(chan, NvSubSw, NV_SW_PAGE_FLIP, 1);
	OUT_RING  (chan, 0x00000000);
	FIRE_RING (chan);

	ret = nouveau_fence_new(chan, false, pfence);
	if (ret)
		goto fail;

	return 0;
fail:
	spin_lock_irqsave(&dev->event_lock, flags);
	list_del(&s->head);
	spin_unlock_irqrestore(&dev->event_lock, flags);
	return ret;
}