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
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  fb_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {int /*<<< orphan*/  filp_head; TYPE_1__ base; } ;
struct drm_file {int /*<<< orphan*/  fbs_lock; int /*<<< orphan*/  fbs; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int PTR_ERR (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_framebuffer* drm_internal_framebuffer_create (struct drm_device*,struct drm_mode_fb_cmd2*,struct drm_file*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_mode_addfb2(struct drm_device *dev,
		    void *data, struct drm_file *file_priv)
{
	struct drm_mode_fb_cmd2 *r = data;
	struct drm_framebuffer *fb;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	fb = drm_internal_framebuffer_create(dev, r, file_priv);
	if (IS_ERR(fb))
		return PTR_ERR(fb);

	DRM_DEBUG_KMS("[FB:%d]\n", fb->base.id);
	r->fb_id = fb->base.id;

	/* Transfer ownership to the filp for reaping on close */
	mutex_lock(&file_priv->fbs_lock);
	list_add(&fb->filp_head, &file_priv->fbs);
	mutex_unlock(&file_priv->fbs_lock);

	return 0;
}