#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct radeon_flip_work {int async; int base; int target_vblank; int /*<<< orphan*/  fence; TYPE_7__* old_rbo; int /*<<< orphan*/  flip_work; int /*<<< orphan*/  crtc_id; struct drm_pending_vblank_event* event; struct radeon_device* rdev; int /*<<< orphan*/  unpin_work; } ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {scalar_t__ flip_status; int /*<<< orphan*/  flip_queue; struct radeon_flip_work* flip_work; scalar_t__ legacy_display_base_addr; int /*<<< orphan*/  crtc_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  resv; } ;
struct TYPE_9__ {TYPE_1__ base; } ;
struct radeon_bo {TYPE_2__ tbo; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; struct drm_gem_object** obj; } ;
struct drm_device {int /*<<< orphan*/  event_lock; TYPE_4__* driver; struct radeon_device* dev_private; } ;
struct drm_crtc {int y; int x; struct drm_device* dev; TYPE_5__* primary; } ;
struct TYPE_13__ {int /*<<< orphan*/  base; } ;
struct TYPE_14__ {TYPE_6__ tbo; } ;
struct TYPE_12__ {struct drm_framebuffer* fb; } ;
struct TYPE_11__ {int (* get_vblank_counter ) (struct drm_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int* cpp; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MODE_PAGE_FLIP_ASYNC ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RADEON_FLIP_NONE ; 
 scalar_t__ RADEON_FLIP_PENDING ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_TILING_MACRO ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_get_excl (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_crtc_vblank_count (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 void* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct radeon_flip_work*) ; 
 struct radeon_flip_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_get_tiling_flags (struct radeon_bo*,int*,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin_restricted (struct radeon_bo*,int /*<<< orphan*/ ,int,int*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 scalar_t__ radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_flip_work_func ; 
 int /*<<< orphan*/  radeon_unpin_work_func ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int radeon_crtc_page_flip_target(struct drm_crtc *crtc,
					struct drm_framebuffer *fb,
					struct drm_pending_vblank_event *event,
					uint32_t page_flip_flags,
					uint32_t target,
					struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_gem_object *obj;
	struct radeon_flip_work *work;
	struct radeon_bo *new_rbo;
	uint32_t tiling_flags, pitch_pixels;
	uint64_t base;
	unsigned long flags;
	int r;

	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (work == NULL)
		return -ENOMEM;

	INIT_WORK(&work->flip_work, radeon_flip_work_func);
	INIT_WORK(&work->unpin_work, radeon_unpin_work_func);

	work->rdev = rdev;
	work->crtc_id = radeon_crtc->crtc_id;
	work->event = event;
	work->async = (page_flip_flags & DRM_MODE_PAGE_FLIP_ASYNC) != 0;

	/* schedule unpin of the old buffer */
	obj = crtc->primary->fb->obj[0];

	/* take a reference to the old object */
	drm_gem_object_get(obj);
	work->old_rbo = gem_to_radeon_bo(obj);

	obj = fb->obj[0];
	new_rbo = gem_to_radeon_bo(obj);

	/* pin the new buffer */
	DRM_DEBUG_DRIVER("flip-ioctl() cur_rbo = %p, new_rbo = %p\n",
			 work->old_rbo, new_rbo);

	r = radeon_bo_reserve(new_rbo, false);
	if (unlikely(r != 0)) {
		DRM_ERROR("failed to reserve new rbo buffer before flip\n");
		goto cleanup;
	}
	/* Only 27 bit offset for legacy CRTC */
	r = radeon_bo_pin_restricted(new_rbo, RADEON_GEM_DOMAIN_VRAM,
				     ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27, &base);
	if (unlikely(r != 0)) {
		radeon_bo_unreserve(new_rbo);
		r = -EINVAL;
		DRM_ERROR("failed to pin new rbo buffer before flip\n");
		goto cleanup;
	}
	work->fence = dma_fence_get(dma_resv_get_excl(new_rbo->tbo.base.resv));
	radeon_bo_get_tiling_flags(new_rbo, &tiling_flags, NULL);
	radeon_bo_unreserve(new_rbo);

	if (!ASIC_IS_AVIVO(rdev)) {
		/* crtc offset is from display base addr not FB location */
		base -= radeon_crtc->legacy_display_base_addr;
		pitch_pixels = fb->pitches[0] / fb->format->cpp[0];

		if (tiling_flags & RADEON_TILING_MACRO) {
			if (ASIC_IS_R300(rdev)) {
				base &= ~0x7ff;
			} else {
				int byteshift = fb->format->cpp[0] * 8 >> 4;
				int tile_addr = (((crtc->y >> 3) * pitch_pixels +  crtc->x) >> (8 - byteshift)) << 11;
				base += tile_addr + ((crtc->x << byteshift) % 256) + ((crtc->y % 8) << 8);
			}
		} else {
			int offset = crtc->y * pitch_pixels + crtc->x;
			switch (fb->format->cpp[0] * 8) {
			case 8:
			default:
				offset *= 1;
				break;
			case 15:
			case 16:
				offset *= 2;
				break;
			case 24:
				offset *= 3;
				break;
			case 32:
				offset *= 4;
				break;
			}
			base += offset;
		}
		base &= ~7;
	}
	work->base = base;
	work->target_vblank = target - (uint32_t)drm_crtc_vblank_count(crtc) +
		dev->driver->get_vblank_counter(dev, work->crtc_id);

	/* We borrow the event spin lock for protecting flip_work */
	spin_lock_irqsave(&crtc->dev->event_lock, flags);

	if (radeon_crtc->flip_status != RADEON_FLIP_NONE) {
		DRM_DEBUG_DRIVER("flip queue: crtc already busy\n");
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		r = -EBUSY;
		goto pflip_cleanup;
	}
	radeon_crtc->flip_status = RADEON_FLIP_PENDING;
	radeon_crtc->flip_work = work;

	/* update crtc fb */
	crtc->primary->fb = fb;

	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

	queue_work(radeon_crtc->flip_queue, &work->flip_work);
	return 0;

pflip_cleanup:
	if (unlikely(radeon_bo_reserve(new_rbo, false) != 0)) {
		DRM_ERROR("failed to reserve new rbo in error path\n");
		goto cleanup;
	}
	if (unlikely(radeon_bo_unpin(new_rbo) != 0)) {
		DRM_ERROR("failed to unpin new rbo in error path\n");
	}
	radeon_bo_unreserve(new_rbo);

cleanup:
	drm_gem_object_put_unlocked(&work->old_rbo->tbo.base);
	dma_fence_put(work->fence);
	kfree(work);
	return r;
}