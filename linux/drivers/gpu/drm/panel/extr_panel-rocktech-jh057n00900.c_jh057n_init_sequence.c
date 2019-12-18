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
struct mipi_dsi_device {int dummy; } ;
struct jh057n {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (struct device*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  ST7703_CMD_SETBGP ; 
 int /*<<< orphan*/  ST7703_CMD_SETCYC ; 
 int /*<<< orphan*/  ST7703_CMD_SETDISP ; 
 int /*<<< orphan*/  ST7703_CMD_SETEQ ; 
 int /*<<< orphan*/  ST7703_CMD_SETEXTC ; 
 int /*<<< orphan*/  ST7703_CMD_SETGAMMA ; 
 int /*<<< orphan*/  ST7703_CMD_SETGIP1 ; 
 int /*<<< orphan*/  ST7703_CMD_SETGIP2 ; 
 int /*<<< orphan*/  ST7703_CMD_SETPANEL ; 
 int /*<<< orphan*/  ST7703_CMD_SETRGBIF ; 
 int /*<<< orphan*/  ST7703_CMD_SETSCR ; 
 int /*<<< orphan*/  ST7703_CMD_SETVCOM ; 
 int /*<<< orphan*/  ST7703_CMD_SETVDC ; 
 int /*<<< orphan*/  ST7703_CMD_UNKNOWN0 ; 
 int /*<<< orphan*/  dsi_generic_write_seq (struct mipi_dsi_device*,int /*<<< orphan*/ ,int,...) ; 
 int mipi_dsi_dcs_exit_sleep_mode (struct mipi_dsi_device*) ; 
 int mipi_dsi_dcs_set_display_on (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (struct device*) ; 

__attribute__((used)) static int jh057n_init_sequence(struct jh057n *ctx)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	struct device *dev = ctx->dev;
	int ret;

	/*
	 * Init sequence was supplied by the panel vendor. Most of the commands
	 * resemble the ST7703 but the number of parameters often don't match
	 * so it's likely a clone.
	 */
	dsi_generic_write_seq(dsi, ST7703_CMD_SETEXTC,
			      0xF1, 0x12, 0x83);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETRGBIF,
			      0x10, 0x10, 0x05, 0x05, 0x03, 0xFF, 0x00, 0x00,
			      0x00, 0x00);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETSCR,
			      0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x08, 0x70,
			      0x00);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETVDC, 0x4E);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETPANEL, 0x0B);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETCYC, 0x80);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETDISP, 0xF0, 0x12, 0x30);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETEQ,
			      0x07, 0x07, 0x0B, 0x0B, 0x03, 0x0B, 0x00, 0x00,
			      0x00, 0x00, 0xFF, 0x00, 0xC0, 0x10);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETBGP, 0x08, 0x08);
	msleep(20);

	dsi_generic_write_seq(dsi, ST7703_CMD_SETVCOM, 0x3F, 0x3F);
	dsi_generic_write_seq(dsi, ST7703_CMD_UNKNOWN0, 0x02, 0x11, 0x00);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETGIP1,
			      0x82, 0x10, 0x06, 0x05, 0x9E, 0x0A, 0xA5, 0x12,
			      0x31, 0x23, 0x37, 0x83, 0x04, 0xBC, 0x27, 0x38,
			      0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00,
			      0x03, 0x00, 0x00, 0x00, 0x75, 0x75, 0x31, 0x88,
			      0x88, 0x88, 0x88, 0x88, 0x88, 0x13, 0x88, 0x64,
			      0x64, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			      0x02, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETGIP2,
			      0x02, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x02, 0x46, 0x02, 0x88,
			      0x88, 0x88, 0x88, 0x88, 0x88, 0x64, 0x88, 0x13,
			      0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			      0x75, 0x88, 0x23, 0x14, 0x00, 0x00, 0x02, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0A,
			      0xA5, 0x00, 0x00, 0x00, 0x00);
	dsi_generic_write_seq(dsi, ST7703_CMD_SETGAMMA,
			      0x00, 0x09, 0x0E, 0x29, 0x2D, 0x3C, 0x41, 0x37,
			      0x07, 0x0B, 0x0D, 0x10, 0x11, 0x0F, 0x10, 0x11,
			      0x18, 0x00, 0x09, 0x0E, 0x29, 0x2D, 0x3C, 0x41,
			      0x37, 0x07, 0x0B, 0x0D, 0x10, 0x11, 0x0F, 0x10,
			      0x11, 0x18);
	msleep(20);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	/* Panel is operational 120 msec after reset */
	msleep(60);
	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret)
		return ret;

	DRM_DEV_DEBUG_DRIVER(dev, "Panel init sequence done\n");
	return 0;
}