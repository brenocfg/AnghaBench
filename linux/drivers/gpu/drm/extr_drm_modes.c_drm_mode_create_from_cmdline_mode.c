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
struct drm_display_mode {int /*<<< orphan*/  type; } ;
struct drm_device {int dummy; } ;
struct drm_cmdline_mode {int xres; int refresh; int /*<<< orphan*/  margins; int /*<<< orphan*/  interlace; scalar_t__ refresh_specified; int /*<<< orphan*/  yres; int /*<<< orphan*/  rb; scalar_t__ cvt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_INTERLACE_HALVE_V ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_USERDEF ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_display_mode* drm_gtf_mode (struct drm_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_fixup_1366x768 (struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 

struct drm_display_mode *
drm_mode_create_from_cmdline_mode(struct drm_device *dev,
				  struct drm_cmdline_mode *cmd)
{
	struct drm_display_mode *mode;

	if (cmd->cvt)
		mode = drm_cvt_mode(dev,
				    cmd->xres, cmd->yres,
				    cmd->refresh_specified ? cmd->refresh : 60,
				    cmd->rb, cmd->interlace,
				    cmd->margins);
	else
		mode = drm_gtf_mode(dev,
				    cmd->xres, cmd->yres,
				    cmd->refresh_specified ? cmd->refresh : 60,
				    cmd->interlace,
				    cmd->margins);
	if (!mode)
		return NULL;

	mode->type |= DRM_MODE_TYPE_USERDEF;
	/* fix up 1368x768: GFT/CVT can't express 1366 width due to alignment */
	if (cmd->xres == 1366)
		drm_mode_fixup_1366x768(mode);
	drm_mode_set_crtcinfo(mode, CRTC_INTERLACE_HALVE_V);
	return mode;
}