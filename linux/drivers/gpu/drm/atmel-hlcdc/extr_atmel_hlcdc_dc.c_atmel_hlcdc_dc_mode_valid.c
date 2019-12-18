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
struct drm_display_mode {int vsync_start; int vdisplay; int vtotal; int vsync_end; int hsync_start; int hdisplay; int htotal; int hsync_end; } ;
struct atmel_hlcdc_dc {TYPE_1__* desc; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int max_spw; int max_hpw; int max_vpw; } ;

/* Variables and functions */
 int MODE_HSYNC ; 
 int MODE_H_ILLEGAL ; 
 int MODE_OK ; 
 int MODE_VSYNC ; 
 int MODE_V_ILLEGAL ; 

enum drm_mode_status
atmel_hlcdc_dc_mode_valid(struct atmel_hlcdc_dc *dc,
			  const struct drm_display_mode *mode)
{
	int vfront_porch = mode->vsync_start - mode->vdisplay;
	int vback_porch = mode->vtotal - mode->vsync_end;
	int vsync_len = mode->vsync_end - mode->vsync_start;
	int hfront_porch = mode->hsync_start - mode->hdisplay;
	int hback_porch = mode->htotal - mode->hsync_end;
	int hsync_len = mode->hsync_end - mode->hsync_start;

	if (hsync_len > dc->desc->max_spw + 1 || hsync_len < 1)
		return MODE_HSYNC;

	if (vsync_len > dc->desc->max_spw + 1 || vsync_len < 1)
		return MODE_VSYNC;

	if (hfront_porch > dc->desc->max_hpw + 1 || hfront_porch < 1 ||
	    hback_porch > dc->desc->max_hpw + 1 || hback_porch < 1 ||
	    mode->hdisplay < 1)
		return MODE_H_ILLEGAL;

	if (vfront_porch > dc->desc->max_vpw + 1 || vfront_porch < 1 ||
	    vback_porch > dc->desc->max_vpw || vback_porch < 0 ||
	    mode->vdisplay < 1)
		return MODE_V_ILLEGAL;

	return MODE_OK;
}