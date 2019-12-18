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
struct mipi_dbi {int dummy; } ;
struct mipi_dbi_dev {int enabled; struct mipi_dbi dbi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  ILI9225_DISPLAY_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_2 ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ili9225_command (struct mipi_dbi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ili9225_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	struct mipi_dbi *dbi = &dbidev->dbi;

	DRM_DEBUG_KMS("\n");

	/*
	 * This callback is not protected by drm_dev_enter/exit since we want to
	 * turn off the display on regular driver unload. It's highly unlikely
	 * that the underlying SPI controller is gone should this be called after
	 * unplug.
	 */

	if (!dbidev->enabled)
		return;

	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x0000);
	msleep(50);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x0007);
	msleep(50);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_1, 0x0a02);

	dbidev->enabled = false;
}