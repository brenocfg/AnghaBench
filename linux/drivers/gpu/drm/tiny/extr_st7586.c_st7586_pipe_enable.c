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
typedef  int u8 ;
struct mipi_dbi {int dummy; } ;
struct mipi_dbi_dev {int rotation; int enabled; struct mipi_dbi dbi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_INVERT_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_OFF ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PARTIAL_AREA ; 
 int /*<<< orphan*/  ST7586_AUTO_READ_CTRL ; 
 int ST7586_DISP_CTRL_MX ; 
 int ST7586_DISP_CTRL_MY ; 
 int /*<<< orphan*/  ST7586_DISP_MODE_GRAY ; 
 int /*<<< orphan*/  ST7586_ENABLE_ANALOG ; 
 int /*<<< orphan*/  ST7586_ENABLE_DDRAM ; 
 int /*<<< orphan*/  ST7586_OTP_CTRL_OUT ; 
 int /*<<< orphan*/  ST7586_OTP_READ ; 
 int /*<<< orphan*/  ST7586_OTP_RW_CTRL ; 
 int /*<<< orphan*/  ST7586_SET_BIAS_SYSTEM ; 
 int /*<<< orphan*/  ST7586_SET_BOOST_LEVEL ; 
 int /*<<< orphan*/  ST7586_SET_DISP_DUTY ; 
 int /*<<< orphan*/  ST7586_SET_NLINE_INV ; 
 int /*<<< orphan*/  ST7586_SET_PART_DISP ; 
 int /*<<< orphan*/  ST7586_SET_VOP ; 
 int /*<<< orphan*/  ST7586_SET_VOP_OFFSET ; 
 int /*<<< orphan*/  drm_dev_enter (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,...) ; 
 int mipi_dbi_poweron_reset (struct mipi_dbi_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  st7586_fb_dirty (struct drm_framebuffer*,struct drm_rect*) ; 

__attribute__((used)) static void st7586_pipe_enable(struct drm_simple_display_pipe *pipe,
			       struct drm_crtc_state *crtc_state,
			       struct drm_plane_state *plane_state)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	struct drm_framebuffer *fb = plane_state->fb;
	struct mipi_dbi *dbi = &dbidev->dbi;
	struct drm_rect rect = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	int idx, ret;
	u8 addr_mode;

	if (!drm_dev_enter(pipe->crtc.dev, &idx))
		return;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_poweron_reset(dbidev);
	if (ret)
		goto out_exit;

	mipi_dbi_command(dbi, ST7586_AUTO_READ_CTRL, 0x9f);
	mipi_dbi_command(dbi, ST7586_OTP_RW_CTRL, 0x00);

	msleep(10);

	mipi_dbi_command(dbi, ST7586_OTP_READ);

	msleep(20);

	mipi_dbi_command(dbi, ST7586_OTP_CTRL_OUT);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_OFF);

	msleep(50);

	mipi_dbi_command(dbi, ST7586_SET_VOP_OFFSET, 0x00);
	mipi_dbi_command(dbi, ST7586_SET_VOP, 0xe3, 0x00);
	mipi_dbi_command(dbi, ST7586_SET_BIAS_SYSTEM, 0x02);
	mipi_dbi_command(dbi, ST7586_SET_BOOST_LEVEL, 0x04);
	mipi_dbi_command(dbi, ST7586_ENABLE_ANALOG, 0x1d);
	mipi_dbi_command(dbi, ST7586_SET_NLINE_INV, 0x00);
	mipi_dbi_command(dbi, ST7586_DISP_MODE_GRAY);
	mipi_dbi_command(dbi, ST7586_ENABLE_DDRAM, 0x02);

	switch (dbidev->rotation) {
	default:
		addr_mode = 0x00;
		break;
	case 90:
		addr_mode = ST7586_DISP_CTRL_MY;
		break;
	case 180:
		addr_mode = ST7586_DISP_CTRL_MX | ST7586_DISP_CTRL_MY;
		break;
	case 270:
		addr_mode = ST7586_DISP_CTRL_MX;
		break;
	}
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);

	mipi_dbi_command(dbi, ST7586_SET_DISP_DUTY, 0x7f);
	mipi_dbi_command(dbi, ST7586_SET_PART_DISP, 0xa0);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PARTIAL_AREA, 0x00, 0x00, 0x00, 0x77);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_INVERT_MODE);

	msleep(100);

	dbidev->enabled = true;
	st7586_fb_dirty(fb, &rect);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
out_exit:
	drm_dev_exit(idx);
}