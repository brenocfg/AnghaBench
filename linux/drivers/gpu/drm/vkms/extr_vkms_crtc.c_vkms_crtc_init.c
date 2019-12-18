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
struct vkms_output {int /*<<< orphan*/  composer_workq; int /*<<< orphan*/  composer_lock; int /*<<< orphan*/  lock; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vkms_output* drm_crtc_to_vkms_output (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkms_crtc_funcs ; 
 int /*<<< orphan*/  vkms_crtc_helper_funcs ; 

int vkms_crtc_init(struct drm_device *dev, struct drm_crtc *crtc,
		   struct drm_plane *primary, struct drm_plane *cursor)
{
	struct vkms_output *vkms_out = drm_crtc_to_vkms_output(crtc);
	int ret;

	ret = drm_crtc_init_with_planes(dev, crtc, primary, cursor,
					&vkms_crtc_funcs, NULL);
	if (ret) {
		DRM_ERROR("Failed to init CRTC\n");
		return ret;
	}

	drm_crtc_helper_add(crtc, &vkms_crtc_helper_funcs);

	spin_lock_init(&vkms_out->lock);
	spin_lock_init(&vkms_out->composer_lock);

	vkms_out->composer_workq = alloc_ordered_workqueue("vkms_composer", 0);
	if (!vkms_out->composer_workq)
		return -ENOMEM;

	return ret;
}