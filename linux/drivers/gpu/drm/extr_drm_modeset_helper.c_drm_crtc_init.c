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
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_funcs {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct drm_plane* create_primary_plane (struct drm_device*) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,int /*<<< orphan*/ *,struct drm_crtc_funcs const*,int /*<<< orphan*/ *) ; 

int drm_crtc_init(struct drm_device *dev, struct drm_crtc *crtc,
		  const struct drm_crtc_funcs *funcs)
{
	struct drm_plane *primary;

	primary = create_primary_plane(dev);
	return drm_crtc_init_with_planes(dev, crtc, primary, NULL, funcs,
					 NULL);
}