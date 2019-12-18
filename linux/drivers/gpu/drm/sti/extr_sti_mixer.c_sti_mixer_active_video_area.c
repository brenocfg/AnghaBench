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
struct sti_mixer {int dummy; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  GAM_MIXER_AVO ; 
 int /*<<< orphan*/  GAM_MIXER_AVS ; 
 int /*<<< orphan*/  bkg_color ; 
 int /*<<< orphan*/  sti_mixer_reg_write (struct sti_mixer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sti_mixer_set_background_area (struct sti_mixer*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  sti_mixer_set_background_color (struct sti_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_mixer_set_background_status (struct sti_mixer*,int) ; 
 int /*<<< orphan*/  sti_mixer_to_str (struct sti_mixer*) ; 
 int sti_vtg_get_line_number (struct drm_display_mode,scalar_t__) ; 
 int sti_vtg_get_pixel_number (struct drm_display_mode,scalar_t__) ; 

int sti_mixer_active_video_area(struct sti_mixer *mixer,
				struct drm_display_mode *mode)
{
	u32 ydo, xdo, yds, xds;

	ydo = sti_vtg_get_line_number(*mode, 0);
	yds = sti_vtg_get_line_number(*mode, mode->vdisplay - 1);
	xdo = sti_vtg_get_pixel_number(*mode, 0);
	xds = sti_vtg_get_pixel_number(*mode, mode->hdisplay - 1);

	DRM_DEBUG_DRIVER("%s active video area xdo:%d ydo:%d xds:%d yds:%d\n",
			 sti_mixer_to_str(mixer), xdo, ydo, xds, yds);
	sti_mixer_reg_write(mixer, GAM_MIXER_AVO, ydo << 16 | xdo);
	sti_mixer_reg_write(mixer, GAM_MIXER_AVS, yds << 16 | xds);

	sti_mixer_set_background_color(mixer, bkg_color);

	sti_mixer_set_background_area(mixer, mode);
	sti_mixer_set_background_status(mixer, true);
	return 0;
}