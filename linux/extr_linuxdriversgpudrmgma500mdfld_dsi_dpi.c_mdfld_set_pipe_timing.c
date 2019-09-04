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
struct mdfld_dsi_config {struct drm_display_mode* mode; struct drm_device* dev; } ;
struct drm_display_mode {int htotal; int hdisplay; int hsync_end; int hsync_start; int vtotal; int vdisplay; int vsync_end; int vsync_start; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBLANK_A ; 
 int /*<<< orphan*/  HSYNC_A ; 
 int /*<<< orphan*/  HTOTAL_A ; 
 int /*<<< orphan*/  PIPEASRC ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VBLANK_A ; 
 int /*<<< orphan*/  VSYNC_A ; 
 int /*<<< orphan*/  VTOTAL_A ; 

__attribute__((used)) static void mdfld_set_pipe_timing(struct mdfld_dsi_config *dsi_config, int pipe)
{
	struct drm_device *dev = dsi_config->dev;
	struct drm_display_mode *mode = dsi_config->mode;

	REG_WRITE(HTOTAL_A, ((mode->htotal - 1) << 16) | (mode->hdisplay - 1));
	REG_WRITE(HBLANK_A, ((mode->htotal - 1) << 16) | (mode->hdisplay - 1));
	REG_WRITE(HSYNC_A,
		((mode->hsync_end - 1) << 16) | (mode->hsync_start - 1));

	REG_WRITE(VTOTAL_A, ((mode->vtotal - 1) << 16) | (mode->vdisplay - 1));
	REG_WRITE(VBLANK_A, ((mode->vtotal - 1) << 16) | (mode->vdisplay - 1));
	REG_WRITE(VSYNC_A,
		((mode->vsync_end - 1) << 16) | (mode->vsync_start - 1));

	REG_WRITE(PIPEASRC,
		((mode->hdisplay - 1) << 16) | (mode->vdisplay - 1));
}