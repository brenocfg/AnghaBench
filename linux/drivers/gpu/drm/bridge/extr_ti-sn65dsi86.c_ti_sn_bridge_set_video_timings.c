#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {TYPE_3__* encoder; } ;
struct ti_sn_bridge {int /*<<< orphan*/  regmap; TYPE_4__ bridge; } ;
struct drm_display_mode {int flags; int hdisplay; int vdisplay; int hsync_end; int hsync_start; int vsync_end; int vsync_start; int htotal; int vtotal; } ;
struct TYPE_7__ {TYPE_2__* crtc; } ;
struct TYPE_6__ {TYPE_1__* state; } ;
struct TYPE_5__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int CHA_HSYNC_POLARITY ; 
 int CHA_VSYNC_POLARITY ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  SN_CHA_ACTIVE_LINE_LENGTH_LOW_REG ; 
 int /*<<< orphan*/  SN_CHA_HORIZONTAL_BACK_PORCH_REG ; 
 int /*<<< orphan*/  SN_CHA_HORIZONTAL_FRONT_PORCH_REG ; 
 int /*<<< orphan*/  SN_CHA_HSYNC_PULSE_WIDTH_HIGH_REG ; 
 int /*<<< orphan*/  SN_CHA_HSYNC_PULSE_WIDTH_LOW_REG ; 
 int /*<<< orphan*/  SN_CHA_VERTICAL_BACK_PORCH_REG ; 
 int /*<<< orphan*/  SN_CHA_VERTICAL_DISPLAY_SIZE_LOW_REG ; 
 int /*<<< orphan*/  SN_CHA_VERTICAL_FRONT_PORCH_REG ; 
 int /*<<< orphan*/  SN_CHA_VSYNC_PULSE_WIDTH_HIGH_REG ; 
 int /*<<< orphan*/  SN_CHA_VSYNC_PULSE_WIDTH_LOW_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_sn_bridge_write_u16 (struct ti_sn_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ti_sn_bridge_set_video_timings(struct ti_sn_bridge *pdata)
{
	struct drm_display_mode *mode =
		&pdata->bridge.encoder->crtc->state->adjusted_mode;
	u8 hsync_polarity = 0, vsync_polarity = 0;

	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		hsync_polarity = CHA_HSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		vsync_polarity = CHA_VSYNC_POLARITY;

	ti_sn_bridge_write_u16(pdata, SN_CHA_ACTIVE_LINE_LENGTH_LOW_REG,
			       mode->hdisplay);
	ti_sn_bridge_write_u16(pdata, SN_CHA_VERTICAL_DISPLAY_SIZE_LOW_REG,
			       mode->vdisplay);
	regmap_write(pdata->regmap, SN_CHA_HSYNC_PULSE_WIDTH_LOW_REG,
		     (mode->hsync_end - mode->hsync_start) & 0xFF);
	regmap_write(pdata->regmap, SN_CHA_HSYNC_PULSE_WIDTH_HIGH_REG,
		     (((mode->hsync_end - mode->hsync_start) >> 8) & 0x7F) |
		     hsync_polarity);
	regmap_write(pdata->regmap, SN_CHA_VSYNC_PULSE_WIDTH_LOW_REG,
		     (mode->vsync_end - mode->vsync_start) & 0xFF);
	regmap_write(pdata->regmap, SN_CHA_VSYNC_PULSE_WIDTH_HIGH_REG,
		     (((mode->vsync_end - mode->vsync_start) >> 8) & 0x7F) |
		     vsync_polarity);

	regmap_write(pdata->regmap, SN_CHA_HORIZONTAL_BACK_PORCH_REG,
		     (mode->htotal - mode->hsync_end) & 0xFF);
	regmap_write(pdata->regmap, SN_CHA_VERTICAL_BACK_PORCH_REG,
		     (mode->vtotal - mode->vsync_end) & 0xFF);

	regmap_write(pdata->regmap, SN_CHA_HORIZONTAL_FRONT_PORCH_REG,
		     (mode->hsync_start - mode->hdisplay) & 0xFF);
	regmap_write(pdata->regmap, SN_CHA_VERTICAL_FRONT_PORCH_REG,
		     (mode->vsync_start - mode->vdisplay) & 0xFF);

	usleep_range(10000, 10500); /* 10ms delay recommended by spec */
}