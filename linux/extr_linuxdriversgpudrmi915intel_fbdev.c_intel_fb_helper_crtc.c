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
struct TYPE_2__ {struct drm_crtc* crtc; } ;
struct drm_fb_helper_crtc {TYPE_1__ mode_set; } ;
struct drm_fb_helper {int crtc_count; struct drm_fb_helper_crtc* crtc_info; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct drm_fb_helper_crtc *
intel_fb_helper_crtc(struct drm_fb_helper *fb_helper, struct drm_crtc *crtc)
{
	int i;

	for (i = 0; i < fb_helper->crtc_count; i++)
		if (fb_helper->crtc_info[i].mode_set.crtc == crtc)
			return &fb_helper->crtc_info[i];

	return NULL;
}