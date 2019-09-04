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
struct drm_mode_set {int x; int y; } ;
struct drm_fb_helper {int crtc_count; TYPE_1__* crtc_info; } ;
struct TYPE_2__ {struct drm_mode_set mode_set; } ;

/* Variables and functions */

__attribute__((used)) static void pan_set(struct drm_fb_helper *fb_helper, int x, int y)
{
	int i;

	for (i = 0; i < fb_helper->crtc_count; i++) {
		struct drm_mode_set *mode_set;

		mode_set = &fb_helper->crtc_info[i].mode_set;

		mode_set->x = x;
		mode_set->y = y;
	}
}