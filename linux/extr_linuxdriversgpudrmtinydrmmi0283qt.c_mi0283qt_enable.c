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
typedef  int u8 ;
struct tinydrm_device {int dummy; } ;
struct mipi_dbi {int rotation; } ;
struct drm_simple_display_pipe {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  ILI9341_DISCTRL ; 
 int /*<<< orphan*/  ILI9341_DTCTRLA ; 
 int /*<<< orphan*/  ILI9341_DTCTRLB ; 
 int /*<<< orphan*/  ILI9341_EN3GAM ; 
 int /*<<< orphan*/  ILI9341_ETMOD ; 
 int /*<<< orphan*/  ILI9341_FRMCTR1 ; 
 int ILI9341_MADCTL_BGR ; 
 int ILI9341_MADCTL_MV ; 
 int ILI9341_MADCTL_MX ; 
 int ILI9341_MADCTL_MY ; 
 int /*<<< orphan*/  ILI9341_NGAMCTRL ; 
 int /*<<< orphan*/  ILI9341_PGAMCTRL ; 
 int /*<<< orphan*/  ILI9341_PUMPCTRL ; 
 int /*<<< orphan*/  ILI9341_PWCTRL1 ; 
 int /*<<< orphan*/  ILI9341_PWCTRL2 ; 
 int /*<<< orphan*/  ILI9341_PWCTRLA ; 
 int /*<<< orphan*/  ILI9341_PWCTRLB ; 
 int /*<<< orphan*/  ILI9341_PWRSEQ ; 
 int /*<<< orphan*/  ILI9341_VMCTRL1 ; 
 int /*<<< orphan*/  ILI9341_VMCTRL2 ; 
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int MIPI_DCS_PIXEL_FMT_16BIT ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_OFF ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_GAMMA_CURVE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mipi_dbi_enable_flush (struct mipi_dbi*,struct drm_crtc_state*,struct drm_plane_state*) ; 
 struct mipi_dbi* mipi_dbi_from_tinydrm (struct tinydrm_device*) ; 
 int mipi_dbi_poweron_conditional_reset (struct mipi_dbi*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct tinydrm_device* pipe_to_tinydrm (struct drm_simple_display_pipe*) ; 

__attribute__((used)) static void mi0283qt_enable(struct drm_simple_display_pipe *pipe,
			    struct drm_crtc_state *crtc_state,
			    struct drm_plane_state *plane_state)
{
	struct tinydrm_device *tdev = pipe_to_tinydrm(pipe);
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);
	u8 addr_mode;
	int ret;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_poweron_conditional_reset(mipi);
	if (ret < 0)
		return;
	if (ret == 1)
		goto out_enable;

	mipi_dbi_command(mipi, MIPI_DCS_SET_DISPLAY_OFF);

	mipi_dbi_command(mipi, ILI9341_PWCTRLB, 0x00, 0x83, 0x30);
	mipi_dbi_command(mipi, ILI9341_PWRSEQ, 0x64, 0x03, 0x12, 0x81);
	mipi_dbi_command(mipi, ILI9341_DTCTRLA, 0x85, 0x01, 0x79);
	mipi_dbi_command(mipi, ILI9341_PWCTRLA, 0x39, 0x2c, 0x00, 0x34, 0x02);
	mipi_dbi_command(mipi, ILI9341_PUMPCTRL, 0x20);
	mipi_dbi_command(mipi, ILI9341_DTCTRLB, 0x00, 0x00);

	/* Power Control */
	mipi_dbi_command(mipi, ILI9341_PWCTRL1, 0x26);
	mipi_dbi_command(mipi, ILI9341_PWCTRL2, 0x11);
	/* VCOM */
	mipi_dbi_command(mipi, ILI9341_VMCTRL1, 0x35, 0x3e);
	mipi_dbi_command(mipi, ILI9341_VMCTRL2, 0xbe);

	/* Memory Access Control */
	mipi_dbi_command(mipi, MIPI_DCS_SET_PIXEL_FORMAT, MIPI_DCS_PIXEL_FMT_16BIT);

	/* Frame Rate */
	mipi_dbi_command(mipi, ILI9341_FRMCTR1, 0x00, 0x1b);

	/* Gamma */
	mipi_dbi_command(mipi, ILI9341_EN3GAM, 0x08);
	mipi_dbi_command(mipi, MIPI_DCS_SET_GAMMA_CURVE, 0x01);
	mipi_dbi_command(mipi, ILI9341_PGAMCTRL,
		       0x1f, 0x1a, 0x18, 0x0a, 0x0f, 0x06, 0x45, 0x87,
		       0x32, 0x0a, 0x07, 0x02, 0x07, 0x05, 0x00);
	mipi_dbi_command(mipi, ILI9341_NGAMCTRL,
		       0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3a, 0x78,
		       0x4d, 0x05, 0x18, 0x0d, 0x38, 0x3a, 0x1f);

	/* DDRAM */
	mipi_dbi_command(mipi, ILI9341_ETMOD, 0x07);

	/* Display */
	mipi_dbi_command(mipi, ILI9341_DISCTRL, 0x0a, 0x82, 0x27, 0x00);
	mipi_dbi_command(mipi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(100);

	mipi_dbi_command(mipi, MIPI_DCS_SET_DISPLAY_ON);
	msleep(100);

out_enable:
	/* The PiTFT (ili9340) has a hardware reset circuit that
	 * resets only on power-on and not on each reboot through
	 * a gpio like the rpi-display does.
	 * As a result, we need to always apply the rotation value
	 * regardless of the display "on/off" state.
	 */
	switch (mipi->rotation) {
	default:
		addr_mode = ILI9341_MADCTL_MV | ILI9341_MADCTL_MY |
			    ILI9341_MADCTL_MX;
		break;
	case 90:
		addr_mode = ILI9341_MADCTL_MY;
		break;
	case 180:
		addr_mode = ILI9341_MADCTL_MV;
		break;
	case 270:
		addr_mode = ILI9341_MADCTL_MX;
		break;
	}
	addr_mode |= ILI9341_MADCTL_BGR;
	mipi_dbi_command(mipi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(mipi, crtc_state, plane_state);
}