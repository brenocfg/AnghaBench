#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vrefresh; } ;
struct drm_display_mode {int clock; scalar_t__ hdisplay; scalar_t__ vdisplay; int flags; } ;
struct TYPE_3__ {struct drm_display_mode mode; } ;
struct nv17_tv_norm_params {scalar_t__ kind; TYPE_2__ tv_enc_mode; TYPE_1__ ctv_enc_mode; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ CTV_ENC_MODE ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int MODE_BAD ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_NO_INTERLACE ; 
 int MODE_OK ; 
 int MODE_VSYNC ; 
 int const abs (scalar_t__) ; 
 int drm_mode_vrefresh (struct drm_display_mode*) ; 
 struct nv17_tv_norm_params* get_tv_norm (struct drm_encoder*) ; 

__attribute__((used)) static int nv17_tv_mode_valid(struct drm_encoder *encoder,
			      struct drm_display_mode *mode)
{
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);

	if (tv_norm->kind == CTV_ENC_MODE) {
		struct drm_display_mode *output_mode =
						&tv_norm->ctv_enc_mode.mode;

		if (mode->clock > 400000)
			return MODE_CLOCK_HIGH;

		if (mode->hdisplay > output_mode->hdisplay ||
		    mode->vdisplay > output_mode->vdisplay)
			return MODE_BAD;

		if ((mode->flags & DRM_MODE_FLAG_INTERLACE) !=
		    (output_mode->flags & DRM_MODE_FLAG_INTERLACE))
			return MODE_NO_INTERLACE;

		if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
			return MODE_NO_DBLESCAN;

	} else {
		const int vsync_tolerance = 600;

		if (mode->clock > 70000)
			return MODE_CLOCK_HIGH;

		if (abs(drm_mode_vrefresh(mode) * 1000 -
			tv_norm->tv_enc_mode.vrefresh) > vsync_tolerance)
			return MODE_VSYNC;

		/* The encoder takes care of the actual interlacing */
		if (mode->flags & DRM_MODE_FLAG_INTERLACE)
			return MODE_NO_INTERLACE;
	}

	return MODE_OK;
}