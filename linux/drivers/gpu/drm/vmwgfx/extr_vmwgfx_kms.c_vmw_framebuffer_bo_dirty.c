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
struct vmw_private {int active_display_unit; int /*<<< orphan*/  dev; int /*<<< orphan*/  reservation_sem; } ;
struct vmw_framebuffer_bo {int /*<<< orphan*/  base; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; scalar_t__ y1; scalar_t__ x1; } ;

/* Variables and functions */
 unsigned int DRM_MODE_FB_DIRTY_ANNOTATE_COPY ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ ) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
#define  vmw_du_legacy 128 
 int /*<<< orphan*/  vmw_fifo_flush (struct vmw_private*,int) ; 
 struct vmw_framebuffer_bo* vmw_framebuffer_to_vfbd (struct drm_framebuffer*) ; 
 int vmw_kms_ldu_do_bo_dirty (struct vmw_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_clip_rect*,unsigned int,int) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_framebuffer_bo_dirty(struct drm_framebuffer *framebuffer,
				    struct drm_file *file_priv,
				    unsigned int flags, unsigned int color,
				    struct drm_clip_rect *clips,
				    unsigned int num_clips)
{
	struct vmw_private *dev_priv = vmw_priv(framebuffer->dev);
	struct vmw_framebuffer_bo *vfbd =
		vmw_framebuffer_to_vfbd(framebuffer);
	struct drm_clip_rect norect;
	int ret, increment = 1;

	drm_modeset_lock_all(dev_priv->dev);

	ret = ttm_read_lock(&dev_priv->reservation_sem, true);
	if (unlikely(ret != 0)) {
		drm_modeset_unlock_all(dev_priv->dev);
		return ret;
	}

	if (!num_clips) {
		num_clips = 1;
		clips = &norect;
		norect.x1 = norect.y1 = 0;
		norect.x2 = framebuffer->width;
		norect.y2 = framebuffer->height;
	} else if (flags & DRM_MODE_FB_DIRTY_ANNOTATE_COPY) {
		num_clips /= 2;
		increment = 2;
	}

	switch (dev_priv->active_display_unit) {
	case vmw_du_legacy:
		ret = vmw_kms_ldu_do_bo_dirty(dev_priv, &vfbd->base, 0, 0,
					      clips, num_clips, increment);
		break;
	default:
		ret = -EINVAL;
		WARN_ONCE(true, "Dirty called with invalid display system.\n");
		break;
	}

	vmw_fifo_flush(dev_priv, false);
	ttm_read_unlock(&dev_priv->reservation_sem);

	drm_modeset_unlock_all(dev_priv->dev);

	return ret;
}