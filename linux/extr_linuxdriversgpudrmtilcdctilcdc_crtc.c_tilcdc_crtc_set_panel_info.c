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
struct tilcdc_panel_info {int dummy; } ;
struct tilcdc_crtc {struct tilcdc_panel_info const* info; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

void tilcdc_crtc_set_panel_info(struct drm_crtc *crtc,
		const struct tilcdc_panel_info *info)
{
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	tilcdc_crtc->info = info;
}