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
struct tegra_dc {TYPE_1__* soc; } ;
struct drm_display_mode {int vsync_end; int vsync_start; int hsync_end; int hsync_start; int vtotal; int htotal; int vdisplay; int hdisplay; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_nvdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DISP_ACTIVE ; 
 int /*<<< orphan*/  DC_DISP_BACK_PORCH ; 
 int /*<<< orphan*/  DC_DISP_DISP_TIMING_OPTIONS ; 
 int /*<<< orphan*/  DC_DISP_FRONT_PORCH ; 
 int /*<<< orphan*/  DC_DISP_REF_TO_SYNC ; 
 int /*<<< orphan*/  DC_DISP_SYNC_WIDTH ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dc_set_timings(struct tegra_dc *dc,
				struct drm_display_mode *mode)
{
	unsigned int h_ref_to_sync = 1;
	unsigned int v_ref_to_sync = 1;
	unsigned long value;

	if (!dc->soc->has_nvdisplay) {
		tegra_dc_writel(dc, 0x0, DC_DISP_DISP_TIMING_OPTIONS);

		value = (v_ref_to_sync << 16) | h_ref_to_sync;
		tegra_dc_writel(dc, value, DC_DISP_REF_TO_SYNC);
	}

	value = ((mode->vsync_end - mode->vsync_start) << 16) |
		((mode->hsync_end - mode->hsync_start) <<  0);
	tegra_dc_writel(dc, value, DC_DISP_SYNC_WIDTH);

	value = ((mode->vtotal - mode->vsync_end) << 16) |
		((mode->htotal - mode->hsync_end) <<  0);
	tegra_dc_writel(dc, value, DC_DISP_BACK_PORCH);

	value = ((mode->vsync_start - mode->vdisplay) << 16) |
		((mode->hsync_start - mode->hdisplay) <<  0);
	tegra_dc_writel(dc, value, DC_DISP_FRONT_PORCH);

	value = (mode->vdisplay << 16) | mode->hdisplay;
	tegra_dc_writel(dc, value, DC_DISP_ACTIVE);

	return 0;
}