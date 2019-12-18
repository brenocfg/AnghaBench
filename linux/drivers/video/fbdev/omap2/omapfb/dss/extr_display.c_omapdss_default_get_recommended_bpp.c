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
struct TYPE_8__ {int /*<<< orphan*/  dsi_pix_fmt; } ;
struct TYPE_7__ {int pixel_size; } ;
struct TYPE_5__ {int data_lines; } ;
struct TYPE_6__ {TYPE_1__ dpi; } ;
struct omap_dss_device {int type; TYPE_4__ panel; TYPE_3__ ctrl; TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OMAP_DISPLAY_TYPE_DBI 134 
#define  OMAP_DISPLAY_TYPE_DPI 133 
#define  OMAP_DISPLAY_TYPE_DSI 132 
#define  OMAP_DISPLAY_TYPE_DVI 131 
#define  OMAP_DISPLAY_TYPE_HDMI 130 
#define  OMAP_DISPLAY_TYPE_SDI 129 
#define  OMAP_DISPLAY_TYPE_VENC 128 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 

int omapdss_default_get_recommended_bpp(struct omap_dss_device *dssdev)
{
	switch (dssdev->type) {
	case OMAP_DISPLAY_TYPE_DPI:
		if (dssdev->phy.dpi.data_lines == 24)
			return 24;
		else
			return 16;

	case OMAP_DISPLAY_TYPE_DBI:
		if (dssdev->ctrl.pixel_size == 24)
			return 24;
		else
			return 16;
	case OMAP_DISPLAY_TYPE_DSI:
		if (dsi_get_pixel_size(dssdev->panel.dsi_pix_fmt) > 16)
			return 24;
		else
			return 16;
	case OMAP_DISPLAY_TYPE_VENC:
	case OMAP_DISPLAY_TYPE_SDI:
	case OMAP_DISPLAY_TYPE_HDMI:
	case OMAP_DISPLAY_TYPE_DVI:
		return 24;
	default:
		BUG();
		return 0;
	}
}