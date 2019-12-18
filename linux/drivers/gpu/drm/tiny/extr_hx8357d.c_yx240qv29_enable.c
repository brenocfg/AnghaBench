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
 int HX8357D_MADCTL_MV ; 
 int HX8357D_MADCTL_MX ; 
 int HX8357D_MADCTL_MY ; 
 int /*<<< orphan*/  HX8357D_SETCOM ; 
 int /*<<< orphan*/  HX8357D_SETCYC ; 
 int /*<<< orphan*/  HX8357D_SETEXTC ; 
 int /*<<< orphan*/  HX8357D_SETGAMMA ; 
 int /*<<< orphan*/  HX8357D_SETOSC ; 
 int /*<<< orphan*/  HX8357D_SETPANEL ; 
 int /*<<< orphan*/  HX8357D_SETPOWER ; 
 int /*<<< orphan*/  HX8357D_SETRGB ; 
 int /*<<< orphan*/  HX8357D_SETSTBA ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int MIPI_DCS_PIXEL_FMT_16BIT ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 int /*<<< orphan*/  MIPI_DCS_SET_TEAR_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_TEAR_SCANLINE ; 
 int /*<<< orphan*/  drm_dev_enter (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mipi_dbi_enable_flush (struct mipi_dbi_dev*,struct drm_crtc_state*,struct drm_plane_state*) ; 
 int mipi_dbi_poweron_conditional_reset (struct mipi_dbi_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void yx240qv29_enable(struct drm_simple_display_pipe *pipe,
			     struct drm_crtc_state *crtc_state,
			     struct drm_plane_state *plane_state)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	struct mipi_dbi *dbi = &dbidev->dbi;
	u8 addr_mode;
	int ret, idx;

	if (!drm_dev_enter(pipe->crtc.dev, &idx))
		return;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_poweron_conditional_reset(dbidev);
	if (ret < 0)
		goto out_exit;
	if (ret == 1)
		goto out_enable;

	/* setextc */
	mipi_dbi_command(dbi, HX8357D_SETEXTC, 0xFF, 0x83, 0x57);
	msleep(150);

	/* setRGB which also enables SDO */
	mipi_dbi_command(dbi, HX8357D_SETRGB, 0x00, 0x00, 0x06, 0x06);

	/* -1.52V */
	mipi_dbi_command(dbi, HX8357D_SETCOM, 0x25);

	/* Normal mode 70Hz, Idle mode 55 Hz */
	mipi_dbi_command(dbi, HX8357D_SETOSC, 0x68);

	/* Set Panel - BGR, Gate direction swapped */
	mipi_dbi_command(dbi, HX8357D_SETPANEL, 0x05);

	mipi_dbi_command(dbi, HX8357D_SETPOWER,
			 0x00,  /* Not deep standby */
			 0x15,  /* BT */
			 0x1C,  /* VSPR */
			 0x1C,  /* VSNR */
			 0x83,  /* AP */
			 0xAA);  /* FS */

	mipi_dbi_command(dbi, HX8357D_SETSTBA,
			 0x50,  /* OPON normal */
			 0x50,  /* OPON idle */
			 0x01,  /* STBA */
			 0x3C,  /* STBA */
			 0x1E,  /* STBA */
			 0x08);  /* GEN */

	mipi_dbi_command(dbi, HX8357D_SETCYC,
			 0x02,  /* NW 0x02 */
			 0x40,  /* RTN */
			 0x00,  /* DIV */
			 0x2A,  /* DUM */
			 0x2A,  /* DUM */
			 0x0D,  /* GDON */
			 0x78);  /* GDOFF */

	mipi_dbi_command(dbi, HX8357D_SETGAMMA,
			 0x02,
			 0x0A,
			 0x11,
			 0x1d,
			 0x23,
			 0x35,
			 0x41,
			 0x4b,
			 0x4b,
			 0x42,
			 0x3A,
			 0x27,
			 0x1B,
			 0x08,
			 0x09,
			 0x03,
			 0x02,
			 0x0A,
			 0x11,
			 0x1d,
			 0x23,
			 0x35,
			 0x41,
			 0x4b,
			 0x4b,
			 0x42,
			 0x3A,
			 0x27,
			 0x1B,
			 0x08,
			 0x09,
			 0x03,
			 0x00,
			 0x01);

	/* 16 bit */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEL_FORMAT,
			 MIPI_DCS_PIXEL_FMT_16BIT);

	/* TE off */
	mipi_dbi_command(dbi, MIPI_DCS_SET_TEAR_ON, 0x00);

	/* tear line */
	mipi_dbi_command(dbi, MIPI_DCS_SET_TEAR_SCANLINE, 0x00, 0x02);

	/* Exit Sleep */
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(150);

	/* display on */
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
	usleep_range(5000, 7000);

out_enable:
	switch (dbidev->rotation) {
	default:
		addr_mode = HX8357D_MADCTL_MX | HX8357D_MADCTL_MY;
		break;
	case 90:
		addr_mode = HX8357D_MADCTL_MV | HX8357D_MADCTL_MY;
		break;
	case 180:
		addr_mode = 0;
		break;
	case 270:
		addr_mode = HX8357D_MADCTL_MV | HX8357D_MADCTL_MX;
		break;
	}
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
out_exit:
	drm_dev_exit(idx);
}