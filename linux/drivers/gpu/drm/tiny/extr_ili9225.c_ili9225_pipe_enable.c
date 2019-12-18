#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mipi_dbi {int dummy; } ;
struct mipi_dbi_dev {int rotation; int enabled; struct mipi_dbi dbi; } ;
struct TYPE_4__ {TYPE_2__* dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_crtc_state {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  ILI9225_BLANK_PERIOD_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_DISPLAY_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_DRIVER_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  ILI9225_ENTRY_MODE ; 
 int /*<<< orphan*/  ILI9225_FRAME_CYCLE_CONTROL ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_10 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_2 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_3 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_4 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_5 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_6 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_7 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_8 ; 
 int /*<<< orphan*/  ILI9225_GAMMA_CONTROL_9 ; 
 int /*<<< orphan*/  ILI9225_GATE_SCAN_CONTROL ; 
 int /*<<< orphan*/  ILI9225_INTERFACE_CONTROL ; 
 int /*<<< orphan*/  ILI9225_LCD_AC_DRIVING_CONTROL ; 
 int /*<<< orphan*/  ILI9225_OSCILLATION_CONTROL ; 
 int /*<<< orphan*/  ILI9225_PARTIAL_DRIVING_POS_1 ; 
 int /*<<< orphan*/  ILI9225_PARTIAL_DRIVING_POS_2 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_2 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_3 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_4 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_5 ; 
 int /*<<< orphan*/  ILI9225_RAM_ADDRESS_SET_1 ; 
 int /*<<< orphan*/  ILI9225_RAM_ADDRESS_SET_2 ; 
 int /*<<< orphan*/  ILI9225_VCI_RECYCLING ; 
 int /*<<< orphan*/  ILI9225_VERTICAL_SCROLL_1 ; 
 int /*<<< orphan*/  ILI9225_VERTICAL_SCROLL_2 ; 
 int /*<<< orphan*/  ILI9225_VERTICAL_SCROLL_3 ; 
 int /*<<< orphan*/  drm_dev_enter (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (TYPE_2__*) ; 
 int ili9225_command (struct mipi_dbi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ili9225_fb_dirty (struct drm_framebuffer*,struct drm_rect*) ; 
 int /*<<< orphan*/  mipi_dbi_hw_reset (struct mipi_dbi*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ili9225_pipe_enable(struct drm_simple_display_pipe *pipe,
				struct drm_crtc_state *crtc_state,
				struct drm_plane_state *plane_state)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	struct drm_framebuffer *fb = plane_state->fb;
	struct device *dev = pipe->crtc.dev->dev;
	struct mipi_dbi *dbi = &dbidev->dbi;
	struct drm_rect rect = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	int ret, idx;
	u8 am_id;

	if (!drm_dev_enter(pipe->crtc.dev, &idx))
		return;

	DRM_DEBUG_KMS("\n");

	mipi_dbi_hw_reset(dbi);

	/*
	 * There don't seem to be two example init sequences that match, so
	 * using the one from the popular Arduino library for this display.
	 * https://github.com/Nkawu/TFT_22_ILI9225/blob/master/src/TFT_22_ILI9225.cpp
	 */

	ret = ili9225_command(dbi, ILI9225_POWER_CONTROL_1, 0x0000);
	if (ret) {
		DRM_DEV_ERROR(dev, "Error sending command %d\n", ret);
		goto out_exit;
	}
	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x0000);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_3, 0x0000);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_4, 0x0000);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_5, 0x0000);

	msleep(40);

	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x0018);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_3, 0x6121);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_4, 0x006f);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_5, 0x495f);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_1, 0x0800);

	msleep(10);

	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x103b);

	msleep(50);

	switch (dbidev->rotation) {
	default:
		am_id = 0x30;
		break;
	case 90:
		am_id = 0x18;
		break;
	case 180:
		am_id = 0x00;
		break;
	case 270:
		am_id = 0x28;
		break;
	}
	ili9225_command(dbi, ILI9225_DRIVER_OUTPUT_CONTROL, 0x011c);
	ili9225_command(dbi, ILI9225_LCD_AC_DRIVING_CONTROL, 0x0100);
	ili9225_command(dbi, ILI9225_ENTRY_MODE, 0x1000 | am_id);
	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x0000);
	ili9225_command(dbi, ILI9225_BLANK_PERIOD_CONTROL_1, 0x0808);
	ili9225_command(dbi, ILI9225_FRAME_CYCLE_CONTROL, 0x1100);
	ili9225_command(dbi, ILI9225_INTERFACE_CONTROL, 0x0000);
	ili9225_command(dbi, ILI9225_OSCILLATION_CONTROL, 0x0d01);
	ili9225_command(dbi, ILI9225_VCI_RECYCLING, 0x0020);
	ili9225_command(dbi, ILI9225_RAM_ADDRESS_SET_1, 0x0000);
	ili9225_command(dbi, ILI9225_RAM_ADDRESS_SET_2, 0x0000);

	ili9225_command(dbi, ILI9225_GATE_SCAN_CONTROL, 0x0000);
	ili9225_command(dbi, ILI9225_VERTICAL_SCROLL_1, 0x00db);
	ili9225_command(dbi, ILI9225_VERTICAL_SCROLL_2, 0x0000);
	ili9225_command(dbi, ILI9225_VERTICAL_SCROLL_3, 0x0000);
	ili9225_command(dbi, ILI9225_PARTIAL_DRIVING_POS_1, 0x00db);
	ili9225_command(dbi, ILI9225_PARTIAL_DRIVING_POS_2, 0x0000);

	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_1, 0x0000);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_2, 0x0808);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_3, 0x080a);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_4, 0x000a);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_5, 0x0a08);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_6, 0x0808);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_7, 0x0000);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_8, 0x0a00);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_9, 0x0710);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_10, 0x0710);

	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x0012);

	msleep(50);

	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x1017);

	dbidev->enabled = true;
	ili9225_fb_dirty(fb, &rect);
out_exit:
	drm_dev_exit(idx);
}