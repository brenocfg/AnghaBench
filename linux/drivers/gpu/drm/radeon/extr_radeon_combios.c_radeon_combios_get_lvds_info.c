#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int u32 ;
struct TYPE_4__ {int hdisplay; int vdisplay; int htotal; int hsync_start; int hsync_end; int vtotal; int vsync_start; int vsync_end; int clock; scalar_t__ flags; } ;
struct radeon_encoder_lvds {int panel_vcc_delay; int panel_pwr_delay; int panel_digon_delay; int panel_blon_delay; int panel_ref_divider; int panel_post_divider; int panel_fb_divider; int use_bios_dividers; int lvds_gen_cntl; TYPE_2__ native_mode; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_2__ native_mode; TYPE_1__ base; } ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_LCD_INFO_TABLE ; 
 int /*<<< orphan*/  CRTC_INTERLACE_HALVE_V ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RADEON_LVDS_2_GREY ; 
 int RADEON_LVDS_4_GREY ; 
 int RADEON_LVDS_BL_CLK_SEL ; 
 int RADEON_LVDS_DTM_POL_LOW ; 
 int RADEON_LVDS_FP_POL_LOW ; 
 int RADEON_LVDS_LP_POL_LOW ; 
 int RADEON_LVDS_NO_FM ; 
 int RADEON_LVDS_PANEL_FORMAT ; 
 int RADEON_LVDS_PANEL_TYPE ; 
 int RBIOS16 (int) ; 
 int RBIOS32 (int) ; 
 int RBIOS8 (int) ; 
 int combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder_lvds* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min_t (int /*<<< orphan*/ ,int,int) ; 
 struct radeon_encoder_lvds* radeon_legacy_get_lvds_info_from_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  u16 ; 

struct radeon_encoder_lvds *radeon_combios_get_lvds_info(struct radeon_encoder
							 *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	uint16_t lcd_info;
	uint32_t panel_setup;
	char stmp[30];
	int tmp, i;
	struct radeon_encoder_lvds *lvds = NULL;

	lcd_info = combios_get_table_offset(dev, COMBIOS_LCD_INFO_TABLE);

	if (lcd_info) {
		lvds = kzalloc(sizeof(struct radeon_encoder_lvds), GFP_KERNEL);

		if (!lvds)
			return NULL;

		for (i = 0; i < 24; i++)
			stmp[i] = RBIOS8(lcd_info + i + 1);
		stmp[24] = 0;

		DRM_INFO("Panel ID String: %s\n", stmp);

		lvds->native_mode.hdisplay = RBIOS16(lcd_info + 0x19);
		lvds->native_mode.vdisplay = RBIOS16(lcd_info + 0x1b);

		DRM_INFO("Panel Size %dx%d\n", lvds->native_mode.hdisplay,
			 lvds->native_mode.vdisplay);

		lvds->panel_vcc_delay = RBIOS16(lcd_info + 0x2c);
		lvds->panel_vcc_delay = min_t(u16, lvds->panel_vcc_delay, 2000);

		lvds->panel_pwr_delay = RBIOS8(lcd_info + 0x24);
		lvds->panel_digon_delay = RBIOS16(lcd_info + 0x38) & 0xf;
		lvds->panel_blon_delay = (RBIOS16(lcd_info + 0x38) >> 4) & 0xf;

		lvds->panel_ref_divider = RBIOS16(lcd_info + 0x2e);
		lvds->panel_post_divider = RBIOS8(lcd_info + 0x30);
		lvds->panel_fb_divider = RBIOS16(lcd_info + 0x31);
		if ((lvds->panel_ref_divider != 0) &&
		    (lvds->panel_fb_divider > 3))
			lvds->use_bios_dividers = true;

		panel_setup = RBIOS32(lcd_info + 0x39);
		lvds->lvds_gen_cntl = 0xff00;
		if (panel_setup & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_PANEL_FORMAT;

		if ((panel_setup >> 4) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_PANEL_TYPE;

		switch ((panel_setup >> 8) & 0x7) {
		case 0:
			lvds->lvds_gen_cntl |= RADEON_LVDS_NO_FM;
			break;
		case 1:
			lvds->lvds_gen_cntl |= RADEON_LVDS_2_GREY;
			break;
		case 2:
			lvds->lvds_gen_cntl |= RADEON_LVDS_4_GREY;
			break;
		default:
			break;
		}

		if ((panel_setup >> 16) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_FP_POL_LOW;

		if ((panel_setup >> 17) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_LP_POL_LOW;

		if ((panel_setup >> 18) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_DTM_POL_LOW;

		if ((panel_setup >> 23) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_BL_CLK_SEL;

		lvds->lvds_gen_cntl |= (panel_setup & 0xf0000000);

		for (i = 0; i < 32; i++) {
			tmp = RBIOS16(lcd_info + 64 + i * 2);
			if (tmp == 0)
				break;

			if ((RBIOS16(tmp) == lvds->native_mode.hdisplay) &&
			    (RBIOS16(tmp + 2) == lvds->native_mode.vdisplay)) {
				u32 hss = (RBIOS16(tmp + 21) - RBIOS16(tmp + 19) - 1) * 8;

				if (hss > lvds->native_mode.hdisplay)
					hss = (10 - 1) * 8;

				lvds->native_mode.htotal = lvds->native_mode.hdisplay +
					(RBIOS16(tmp + 17) - RBIOS16(tmp + 19)) * 8;
				lvds->native_mode.hsync_start = lvds->native_mode.hdisplay +
					hss;
				lvds->native_mode.hsync_end = lvds->native_mode.hsync_start +
					(RBIOS8(tmp + 23) * 8);

				lvds->native_mode.vtotal = lvds->native_mode.vdisplay +
					(RBIOS16(tmp + 24) - RBIOS16(tmp + 26));
				lvds->native_mode.vsync_start = lvds->native_mode.vdisplay +
					((RBIOS16(tmp + 28) & 0x7ff) - RBIOS16(tmp + 26));
				lvds->native_mode.vsync_end = lvds->native_mode.vsync_start +
					((RBIOS16(tmp + 28) & 0xf800) >> 11);

				lvds->native_mode.clock = RBIOS16(tmp + 9) * 10;
				lvds->native_mode.flags = 0;
				/* set crtc values */
				drm_mode_set_crtcinfo(&lvds->native_mode, CRTC_INTERLACE_HALVE_V);

			}
		}
	} else {
		DRM_INFO("No panel info found in BIOS\n");
		lvds = radeon_legacy_get_lvds_info_from_regs(rdev);
	}

	if (lvds)
		encoder->native_mode = lvds->native_mode;
	return lvds;
}