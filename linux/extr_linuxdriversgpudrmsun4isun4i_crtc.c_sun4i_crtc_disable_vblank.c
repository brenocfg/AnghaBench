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
struct sun4i_crtc {int /*<<< orphan*/  tcon; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,struct drm_crtc*) ; 
 struct sun4i_crtc* drm_crtc_to_sun4i_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  sun4i_tcon_enable_vblank (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun4i_crtc_disable_vblank(struct drm_crtc *crtc)
{
	struct sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	DRM_DEBUG_DRIVER("Disabling VBLANK on crtc %p\n", crtc);

	sun4i_tcon_enable_vblank(scrtc->tcon, false);
}