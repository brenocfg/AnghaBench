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
struct nouveau_crtc {int /*<<< orphan*/  vblank; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct drm_crtc* drm_crtc_from_index (struct drm_device*,unsigned int) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nvif_notify_get (int /*<<< orphan*/ *) ; 

int
nouveau_display_vblank_enable(struct drm_device *dev, unsigned int pipe)
{
	struct drm_crtc *crtc;
	struct nouveau_crtc *nv_crtc;

	crtc = drm_crtc_from_index(dev, pipe);
	if (!crtc)
		return -EINVAL;

	nv_crtc = nouveau_crtc(crtc);
	nvif_notify_get(&nv_crtc->vblank);

	return 0;
}