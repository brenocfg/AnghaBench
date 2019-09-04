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
struct drm_crtc_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_crtc*,int /*<<< orphan*/ ) ;} ;
struct drm_crtc {struct drm_crtc_helper_funcs* helper_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int /*<<< orphan*/ ) ; 

void gma_crtc_commit(struct drm_crtc *crtc)
{
	const struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
	crtc_funcs->dpms(crtc, DRM_MODE_DPMS_ON);
}