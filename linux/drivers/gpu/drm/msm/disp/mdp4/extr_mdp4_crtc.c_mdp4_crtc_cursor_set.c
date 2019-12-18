#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  void* uint32_t ;
struct msm_kms {int /*<<< orphan*/  aspace; } ;
struct TYPE_3__ {struct msm_kms base; } ;
struct mdp4_kms {TYPE_1__ base; } ;
struct TYPE_4__ {int stale; int /*<<< orphan*/  lock; void* height; void* width; scalar_t__ next_iova; struct drm_gem_object* next_bo; } ;
struct mdp4_crtc {int /*<<< orphan*/  unref_cursor_work; TYPE_2__ cursor; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 void* CURSOR_HEIGHT ; 
 void* CURSOR_WIDTH ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  PENDING_CURSOR ; 
 int /*<<< orphan*/  drm_flip_work_queue (int /*<<< orphan*/ *,struct drm_gem_object*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,void*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct mdp4_kms* get_kms (struct drm_crtc*) ; 
 int msm_gem_get_and_pin_iova (struct drm_gem_object*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  request_pending (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int mdp4_crtc_cursor_set(struct drm_crtc *crtc,
		struct drm_file *file_priv, uint32_t handle,
		uint32_t width, uint32_t height)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct mdp4_kms *mdp4_kms = get_kms(crtc);
	struct msm_kms *kms = &mdp4_kms->base.base;
	struct drm_device *dev = crtc->dev;
	struct drm_gem_object *cursor_bo, *old_bo;
	unsigned long flags;
	uint64_t iova;
	int ret;

	if ((width > CURSOR_WIDTH) || (height > CURSOR_HEIGHT)) {
		DRM_DEV_ERROR(dev->dev, "bad cursor size: %dx%d\n", width, height);
		return -EINVAL;
	}

	if (handle) {
		cursor_bo = drm_gem_object_lookup(file_priv, handle);
		if (!cursor_bo)
			return -ENOENT;
	} else {
		cursor_bo = NULL;
	}

	if (cursor_bo) {
		ret = msm_gem_get_and_pin_iova(cursor_bo, kms->aspace, &iova);
		if (ret)
			goto fail;
	} else {
		iova = 0;
	}

	spin_lock_irqsave(&mdp4_crtc->cursor.lock, flags);
	old_bo = mdp4_crtc->cursor.next_bo;
	mdp4_crtc->cursor.next_bo   = cursor_bo;
	mdp4_crtc->cursor.next_iova = iova;
	mdp4_crtc->cursor.width     = width;
	mdp4_crtc->cursor.height    = height;
	mdp4_crtc->cursor.stale     = true;
	spin_unlock_irqrestore(&mdp4_crtc->cursor.lock, flags);

	if (old_bo) {
		/* drop our previous reference: */
		drm_flip_work_queue(&mdp4_crtc->unref_cursor_work, old_bo);
	}

	request_pending(crtc, PENDING_CURSOR);

	return 0;

fail:
	drm_gem_object_put_unlocked(cursor_bo);
	return ret;
}