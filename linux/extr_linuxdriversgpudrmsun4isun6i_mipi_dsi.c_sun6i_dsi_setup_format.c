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
typedef  int u32 ;
typedef  int u16 ;
struct sun6i_dsi {int /*<<< orphan*/  regs; struct mipi_dsi_device* device; } ;
struct mipi_dsi_device {int format; int /*<<< orphan*/  channel; } ;
struct drm_display_mode {int hdisplay; } ;

/* Variables and functions */
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int MIPI_DSI_PACKED_PIXEL_STREAM_16 ; 
 int MIPI_DSI_PACKED_PIXEL_STREAM_18 ; 
 int MIPI_DSI_PACKED_PIXEL_STREAM_24 ; 
 int MIPI_DSI_PIXEL_STREAM_3BYTE_18 ; 
 int SUN6I_DSI_PIXEL_CTL0_FORMAT (int) ; 
 int SUN6I_DSI_PIXEL_CTL0_PD_PLUG_DISABLE ; 
 int /*<<< orphan*/  SUN6I_DSI_PIXEL_CTL0_REG ; 
 int SUN6I_DSI_PIXEL_PF0_CRC_FORCE (int) ; 
 int /*<<< orphan*/  SUN6I_DSI_PIXEL_PF0_REG ; 
 int SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINE0 (int) ; 
 int SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINEN (int) ; 
 int /*<<< orphan*/  SUN6I_DSI_PIXEL_PF1_REG ; 
 int SUN6I_DSI_PIXEL_PH_DT (int) ; 
 int SUN6I_DSI_PIXEL_PH_ECC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN6I_DSI_PIXEL_PH_REG ; 
 int SUN6I_DSI_PIXEL_PH_VC (int /*<<< orphan*/ ) ; 
 int SUN6I_DSI_PIXEL_PH_WC (int) ; 
 int mipi_dsi_pixel_format_to_bpp (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun6i_dsi_ecc_compute (int) ; 

__attribute__((used)) static void sun6i_dsi_setup_format(struct sun6i_dsi *dsi,
				   struct drm_display_mode *mode)
{
	struct mipi_dsi_device *device = dsi->device;
	u32 val = SUN6I_DSI_PIXEL_PH_VC(device->channel);
	u8 dt, fmt;
	u16 wc;

	/*
	 * TODO: The format defines are only valid in video mode and
	 * change in command mode.
	 */
	switch (device->format) {
	case MIPI_DSI_FMT_RGB888:
		dt = MIPI_DSI_PACKED_PIXEL_STREAM_24;
		fmt = 8;
		break;
	case MIPI_DSI_FMT_RGB666:
		dt = MIPI_DSI_PIXEL_STREAM_3BYTE_18;
		fmt = 9;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		dt = MIPI_DSI_PACKED_PIXEL_STREAM_18;
		fmt = 10;
		break;
	case MIPI_DSI_FMT_RGB565:
		dt = MIPI_DSI_PACKED_PIXEL_STREAM_16;
		fmt = 11;
		break;
	default:
		return;
	}
	val |= SUN6I_DSI_PIXEL_PH_DT(dt);

	wc = mode->hdisplay * mipi_dsi_pixel_format_to_bpp(device->format) / 8;
	val |= SUN6I_DSI_PIXEL_PH_WC(wc);
	val |= SUN6I_DSI_PIXEL_PH_ECC(sun6i_dsi_ecc_compute(val));

	regmap_write(dsi->regs, SUN6I_DSI_PIXEL_PH_REG, val);

	regmap_write(dsi->regs, SUN6I_DSI_PIXEL_PF0_REG,
		     SUN6I_DSI_PIXEL_PF0_CRC_FORCE(0xffff));

	regmap_write(dsi->regs, SUN6I_DSI_PIXEL_PF1_REG,
		     SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINE0(0xffff) |
		     SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINEN(0xffff));

	regmap_write(dsi->regs, SUN6I_DSI_PIXEL_CTL0_REG,
		     SUN6I_DSI_PIXEL_CTL0_PD_PLUG_DISABLE |
		     SUN6I_DSI_PIXEL_CTL0_FORMAT(fmt));
}