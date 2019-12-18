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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; } ;
struct sti_mixer {struct drm_crtc drm_crtc; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sti_crtc_funcs ; 
 int /*<<< orphan*/  sti_crtc_helper_funcs ; 
 int /*<<< orphan*/  sti_mixer_to_str (struct sti_mixer*) ; 

int sti_crtc_init(struct drm_device *drm_dev, struct sti_mixer *mixer,
		  struct drm_plane *primary, struct drm_plane *cursor)
{
	struct drm_crtc *crtc = &mixer->drm_crtc;
	int res;

	res = drm_crtc_init_with_planes(drm_dev, crtc, primary, cursor,
					&sti_crtc_funcs, NULL);
	if (res) {
		DRM_ERROR("Can't initialize CRTC\n");
		return -EINVAL;
	}

	drm_crtc_helper_add(crtc, &sti_crtc_helper_funcs);

	DRM_DEBUG_DRIVER("drm CRTC:%d mapped to %s\n",
			 crtc->base.id, sti_mixer_to_str(mixer));

	return 0;
}