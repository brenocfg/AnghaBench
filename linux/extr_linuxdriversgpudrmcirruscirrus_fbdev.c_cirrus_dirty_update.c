#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {int dummy; } ;
struct cirrus_fbdev {int y1; int y2; int x1; int x2; scalar_t__ sysram; TYPE_2__* gfb; int /*<<< orphan*/  dirty_lock; } ;
struct TYPE_8__ {scalar_t__ virtual; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_pages; } ;
struct cirrus_bo {TYPE_3__ kmap; TYPE_4__ bo; } ;
struct TYPE_7__ {int* pitches; struct drm_gem_object** obj; TYPE_1__* format; } ;
struct TYPE_6__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EBUSY ; 
 int INT_MAX ; 
 int cirrus_bo_reserve (struct cirrus_bo*,int) ; 
 int /*<<< orphan*/  cirrus_bo_unreserve (struct cirrus_bo*) ; 
 scalar_t__ drm_can_sleep () ; 
 struct cirrus_bo* gem_to_cirrus_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int ttm_bo_kmap (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (TYPE_3__*) ; 

__attribute__((used)) static void cirrus_dirty_update(struct cirrus_fbdev *afbdev,
			     int x, int y, int width, int height)
{
	int i;
	struct drm_gem_object *obj;
	struct cirrus_bo *bo;
	int src_offset, dst_offset;
	int bpp = afbdev->gfb->format->cpp[0];
	int ret = -EBUSY;
	bool unmap = false;
	bool store_for_later = false;
	int x2, y2;
	unsigned long flags;

	obj = afbdev->gfb->obj[0];
	bo = gem_to_cirrus_bo(obj);

	/*
	 * try and reserve the BO, if we fail with busy
	 * then the BO is being moved and we should
	 * store up the damage until later.
	 */
	if (drm_can_sleep())
		ret = cirrus_bo_reserve(bo, true);
	if (ret) {
		if (ret != -EBUSY)
			return;
		store_for_later = true;
	}

	x2 = x + width - 1;
	y2 = y + height - 1;
	spin_lock_irqsave(&afbdev->dirty_lock, flags);

	if (afbdev->y1 < y)
		y = afbdev->y1;
	if (afbdev->y2 > y2)
		y2 = afbdev->y2;
	if (afbdev->x1 < x)
		x = afbdev->x1;
	if (afbdev->x2 > x2)
		x2 = afbdev->x2;

	if (store_for_later) {
		afbdev->x1 = x;
		afbdev->x2 = x2;
		afbdev->y1 = y;
		afbdev->y2 = y2;
		spin_unlock_irqrestore(&afbdev->dirty_lock, flags);
		return;
	}

	afbdev->x1 = afbdev->y1 = INT_MAX;
	afbdev->x2 = afbdev->y2 = 0;
	spin_unlock_irqrestore(&afbdev->dirty_lock, flags);

	if (!bo->kmap.virtual) {
		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret) {
			DRM_ERROR("failed to kmap fb updates\n");
			cirrus_bo_unreserve(bo);
			return;
		}
		unmap = true;
	}
	for (i = y; i < y + height; i++) {
		/* assume equal stride for now */
		src_offset = dst_offset = i * afbdev->gfb->pitches[0] + (x * bpp);
		memcpy_toio(bo->kmap.virtual + src_offset, afbdev->sysram + src_offset, width * bpp);

	}
	if (unmap)
		ttm_bo_kunmap(&bo->kmap);

	cirrus_bo_unreserve(bo);
}