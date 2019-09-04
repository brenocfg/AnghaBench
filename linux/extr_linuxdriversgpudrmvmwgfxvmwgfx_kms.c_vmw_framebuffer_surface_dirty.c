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
struct vmw_private {scalar_t__ active_display_unit; int /*<<< orphan*/  dev; int /*<<< orphan*/  reservation_sem; } ;
struct vmw_framebuffer_surface {int /*<<< orphan*/  base; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; scalar_t__ y1; scalar_t__ x1; } ;

/* Variables and functions */
 unsigned int DRM_MODE_FB_DIRTY_ANNOTATE_COPY ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ ) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vmw_du_legacy ; 
 scalar_t__ vmw_du_screen_object ; 
 int /*<<< orphan*/  vmw_fifo_flush (struct vmw_private*,int) ; 
 struct vmw_framebuffer_surface* vmw_framebuffer_to_vfbs (struct drm_framebuffer*) ; 
 int vmw_kms_sou_do_surface_dirty (struct vmw_private*,int /*<<< orphan*/ *,struct drm_clip_rect*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vmw_kms_stdu_surface_dirty (struct vmw_private*,int /*<<< orphan*/ *,struct drm_clip_rect*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_framebuffer_surface_dirty(struct drm_framebuffer *framebuffer,
				  struct drm_file *file_priv,
				  unsigned flags, unsigned color,
				  struct drm_clip_rect *clips,
				  unsigned num_clips)
{
	struct vmw_private *dev_priv = vmw_priv(framebuffer->dev);
	struct vmw_framebuffer_surface *vfbs =
		vmw_framebuffer_to_vfbs(framebuffer);
	struct drm_clip_rect norect;
	int ret, inc = 1;

	/* Legacy Display Unit does not support 3D */
	if (dev_priv->active_display_unit == vmw_du_legacy)
		return -EINVAL;

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
		inc = 2; /* skip source rects */
	}

	if (dev_priv->active_display_unit == vmw_du_screen_object)
		ret = vmw_kms_sou_do_surface_dirty(dev_priv, &vfbs->base,
						   clips, NULL, NULL, 0, 0,
						   num_clips, inc, NULL, NULL);
	else
		ret = vmw_kms_stdu_surface_dirty(dev_priv, &vfbs->base,
						 clips, NULL, NULL, 0, 0,
						 num_clips, inc, NULL, NULL);

	vmw_fifo_flush(dev_priv, false);
	ttm_read_unlock(&dev_priv->reservation_sem);

	drm_modeset_unlock_all(dev_priv->dev);

	return 0;
}