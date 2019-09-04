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
typedef  int u32 ;
struct drm_display_mode {int crtc_hdisplay; int crtc_htotal; int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 

__attribute__((used)) static unsigned int htotal_calculate(struct drm_display_mode *mode)
{
	u32 htotal, new_crtc_htotal;

	htotal = (mode->crtc_hdisplay - 1) | ((mode->crtc_htotal - 1) << 16);

	/*
	 * 1024 x 768  new_crtc_htotal = 0x1024;
	 * 1280 x 1024 new_crtc_htotal = 0x0c34;
	 */
	new_crtc_htotal = (mode->crtc_htotal - 1) * 200 * 1000 / mode->clock;

	DRM_DEBUG_KMS("new crtc htotal 0x%4x\n", new_crtc_htotal);
	return (mode->crtc_hdisplay - 1) | (new_crtc_htotal << 16);
}