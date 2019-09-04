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
struct vc4_crtc {int vblank_enabled; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int vc4_fkms_enable_vblank(struct drm_crtc *crtc)
{
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);

	vc4_crtc->vblank_enabled = true;

	return 0;
}