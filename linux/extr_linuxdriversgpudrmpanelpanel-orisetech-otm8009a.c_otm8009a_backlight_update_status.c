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
struct otm8009a {int /*<<< orphan*/  prepared; } ;
struct TYPE_2__ {scalar_t__ power; int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int ENXIO ; 
 scalar_t__ FB_BLANK_NORMAL ; 
 int MIPI_DCS_SET_DISPLAY_BRIGHTNESS ; 
 int MIPI_DCS_WRITE_CONTROL_DISPLAY ; 
 struct otm8009a* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  otm8009a_dcs_write_buf_hs (struct otm8009a*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otm8009a_backlight_update_status(struct backlight_device *bd)
{
	struct otm8009a *ctx = bl_get_data(bd);
	u8 data[2];

	if (!ctx->prepared) {
		DRM_DEBUG("lcd not ready yet for setting its backlight!\n");
		return -ENXIO;
	}

	if (bd->props.power <= FB_BLANK_NORMAL) {
		/* Power on the backlight with the requested brightness
		 * Note We can not use mipi_dsi_dcs_set_display_brightness()
		 * as otm8009a driver support only 8-bit brightness (1 param).
		 */
		data[0] = MIPI_DCS_SET_DISPLAY_BRIGHTNESS;
		data[1] = bd->props.brightness;
		otm8009a_dcs_write_buf_hs(ctx, data, ARRAY_SIZE(data));

		/* set Brightness Control & Backlight on */
		data[1] = 0x24;

	} else {
		/* Power off the backlight: set Brightness Control & Bl off */
		data[1] = 0;
	}

	/* Update Brightness Control & Backlight */
	data[0] = MIPI_DCS_WRITE_CONTROL_DISPLAY;
	otm8009a_dcs_write_buf_hs(ctx, data, ARRAY_SIZE(data));

	return 0;
}