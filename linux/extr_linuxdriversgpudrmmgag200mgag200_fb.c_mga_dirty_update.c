#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ virtual; } ;
struct TYPE_11__ {int /*<<< orphan*/  num_pages; } ;
struct mgag200_bo {TYPE_4__ kmap; TYPE_5__ bo; } ;
struct TYPE_8__ {int* pitches; TYPE_1__* format; } ;
struct TYPE_9__ {TYPE_2__ base; struct drm_gem_object* obj; } ;
struct mga_fbdev {int y1; int y2; int x1; int x2; scalar_t__ sysram; TYPE_3__ mfb; int /*<<< orphan*/  dirty_lock; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_7__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EBUSY ; 
 int INT_MAX ; 
 scalar_t__ drm_can_sleep () ; 
 struct mgag200_bo* gem_to_mga_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,scalar_t__,int) ; 
 int mgag200_bo_reserve (struct mgag200_bo*,int) ; 
 int /*<<< orphan*/  mgag200_bo_unreserve (struct mgag200_bo*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int ttm_bo_kmap (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (TYPE_4__*) ; 

__attribute__((used)) static void mga_dirty_update(struct mga_fbdev *mfbdev,
			     int x, int y, int width, int height)
{
	int i;
	struct drm_gem_object *obj;
	struct mgag200_bo *bo;
	int src_offset, dst_offset;
	int bpp = mfbdev->mfb.base.format->cpp[0];
	int ret = -EBUSY;
	bool unmap = false;
	bool store_for_later = false;
	int x2, y2;
	unsigned long flags;

	obj = mfbdev->mfb.obj;
	bo = gem_to_mga_bo(obj);

	/*
	 * try and reserve the BO, if we fail with busy
	 * then the BO is being moved and we should
	 * store up the damage until later.
	 */
	if (drm_can_sleep())
		ret = mgag200_bo_reserve(bo, true);
	if (ret) {
		if (ret != -EBUSY)
			return;

		store_for_later = true;
	}

	x2 = x + width - 1;
	y2 = y + height - 1;
	spin_lock_irqsave(&mfbdev->dirty_lock, flags);

	if (mfbdev->y1 < y)
		y = mfbdev->y1;
	if (mfbdev->y2 > y2)
		y2 = mfbdev->y2;
	if (mfbdev->x1 < x)
		x = mfbdev->x1;
	if (mfbdev->x2 > x2)
		x2 = mfbdev->x2;

	if (store_for_later) {
		mfbdev->x1 = x;
		mfbdev->x2 = x2;
		mfbdev->y1 = y;
		mfbdev->y2 = y2;
		spin_unlock_irqrestore(&mfbdev->dirty_lock, flags);
		return;
	}

	mfbdev->x1 = mfbdev->y1 = INT_MAX;
	mfbdev->x2 = mfbdev->y2 = 0;
	spin_unlock_irqrestore(&mfbdev->dirty_lock, flags);

	if (!bo->kmap.virtual) {
		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret) {
			DRM_ERROR("failed to kmap fb updates\n");
			mgag200_bo_unreserve(bo);
			return;
		}
		unmap = true;
	}
	for (i = y; i <= y2; i++) {
		/* assume equal stride for now */
		src_offset = dst_offset = i * mfbdev->mfb.base.pitches[0] + (x * bpp);
		memcpy_toio(bo->kmap.virtual + src_offset, mfbdev->sysram + src_offset, (x2 - x + 1) * bpp);

	}
	if (unmap)
		ttm_bo_kunmap(&bo->kmap);

	mgag200_bo_unreserve(bo);
}