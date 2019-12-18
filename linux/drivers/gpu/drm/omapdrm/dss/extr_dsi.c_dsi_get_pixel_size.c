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
typedef  enum omap_dss_dsi_pixel_format { ____Placeholder_omap_dss_dsi_pixel_format } omap_dss_dsi_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OMAP_DSS_DSI_FMT_RGB565 131 
#define  OMAP_DSS_DSI_FMT_RGB666 130 
#define  OMAP_DSS_DSI_FMT_RGB666_PACKED 129 
#define  OMAP_DSS_DSI_FMT_RGB888 128 

__attribute__((used)) static u8 dsi_get_pixel_size(enum omap_dss_dsi_pixel_format fmt)
{
	switch (fmt) {
	case OMAP_DSS_DSI_FMT_RGB888:
	case OMAP_DSS_DSI_FMT_RGB666:
		return 24;
	case OMAP_DSS_DSI_FMT_RGB666_PACKED:
		return 18;
	case OMAP_DSS_DSI_FMT_RGB565:
		return 16;
	default:
		BUG();
		return 0;
	}
}