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
struct mipi_dbi_dev {int rotation; struct mipi_dbi dbi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;
struct drm_plane_state {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  MIPI_DCS_ENTER_NORMAL_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_INVERT_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_PIXEL_FMT_16BIT ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 int /*<<< orphan*/  ST7735R_FRMCTR1 ; 
 int /*<<< orphan*/  ST7735R_FRMCTR2 ; 
 int /*<<< orphan*/  ST7735R_FRMCTR3 ; 
 int /*<<< orphan*/  ST7735R_GAMCTRN1 ; 
 int /*<<< orphan*/  ST7735R_GAMCTRP1 ; 
 int /*<<< orphan*/  ST7735R_INVCTR ; 
 int ST7735R_MV ; 
 int ST7735R_MX ; 
 int ST7735R_MY ; 
 int /*<<< orphan*/  ST7735R_PWCTR1 ; 
 int /*<<< orphan*/  ST7735R_PWCTR2 ; 
 int /*<<< orphan*/  ST7735R_PWCTR3 ; 
 int /*<<< orphan*/  ST7735R_PWCTR4 ; 
 int /*<<< orphan*/  ST7735R_PWCTR5 ; 
 int /*<<< orphan*/  ST7735R_VMCTR1 ; 
 int /*<<< orphan*/  drm_dev_enter (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mipi_dbi_enable_flush (struct mipi_dbi_dev*,struct drm_crtc_state*,struct drm_plane_state*) ; 
 int mipi_dbi_poweron_reset (struct mipi_dbi_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void jd_t18003_t01_pipe_enable(struct drm_simple_display_pipe *pipe,
				      struct drm_crtc_state *crtc_state,
				      struct drm_plane_state *plane_state)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	struct mipi_dbi *dbi = &dbidev->dbi;
	int ret, idx;
	u8 addr_mode;

	if (!drm_dev_enter(pipe->crtc.dev, &idx))
		return;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_poweron_reset(dbidev);
	if (ret)
		goto out_exit;

	msleep(150);

	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(500);

	mipi_dbi_command(dbi, ST7735R_FRMCTR1, 0x01, 0x2c, 0x2d);
	mipi_dbi_command(dbi, ST7735R_FRMCTR2, 0x01, 0x2c, 0x2d);
	mipi_dbi_command(dbi, ST7735R_FRMCTR3, 0x01, 0x2c, 0x2d, 0x01, 0x2c,
			 0x2d);
	mipi_dbi_command(dbi, ST7735R_INVCTR, 0x07);
	mipi_dbi_command(dbi, ST7735R_PWCTR1, 0xa2, 0x02, 0x84);
	mipi_dbi_command(dbi, ST7735R_PWCTR2, 0xc5);
	mipi_dbi_command(dbi, ST7735R_PWCTR3, 0x0a, 0x00);
	mipi_dbi_command(dbi, ST7735R_PWCTR4, 0x8a, 0x2a);
	mipi_dbi_command(dbi, ST7735R_PWCTR5, 0x8a, 0xee);
	mipi_dbi_command(dbi, ST7735R_VMCTR1, 0x0e);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_INVERT_MODE);
	switch (dbidev->rotation) {
	default:
		addr_mode = ST7735R_MX | ST7735R_MY;
		break;
	case 90:
		addr_mode = ST7735R_MX | ST7735R_MV;
		break;
	case 180:
		addr_mode = 0;
		break;
	case 270:
		addr_mode = ST7735R_MY | ST7735R_MV;
		break;
	}
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEL_FORMAT,
			 MIPI_DCS_PIXEL_FMT_16BIT);
	mipi_dbi_command(dbi, ST7735R_GAMCTRP1, 0x02, 0x1c, 0x07, 0x12, 0x37,
			 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2b, 0x39, 0x00, 0x01,
			 0x03, 0x10);
	mipi_dbi_command(dbi, ST7735R_GAMCTRN1, 0x03, 0x1d, 0x07, 0x06, 0x2e,
			 0x2c, 0x29, 0x2d, 0x2e, 0x2e, 0x37, 0x3f, 0x00, 0x00,
			 0x02, 0x10);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);

	msleep(100);

	mipi_dbi_command(dbi, MIPI_DCS_ENTER_NORMAL_MODE);

	msleep(20);

	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
out_exit:
	drm_dev_exit(idx);
}