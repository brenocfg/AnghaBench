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
typedef  enum mipi_dsi_pixel_format { ____Placeholder_mipi_dsi_pixel_format } mipi_dsi_pixel_format ;
typedef  enum dsi_color { ____Placeholder_dsi_color } dsi_color ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int DSI_RGB565_CONF1 ; 
 int DSI_RGB666_CONF1 ; 
 int DSI_RGB666_CONF2 ; 
 int DSI_RGB888 ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 

__attribute__((used)) static enum dsi_color dsi_color_from_mipi(enum mipi_dsi_pixel_format fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_RGB888:
		return DSI_RGB888;
	case MIPI_DSI_FMT_RGB666:
		return DSI_RGB666_CONF2;
	case MIPI_DSI_FMT_RGB666_PACKED:
		return DSI_RGB666_CONF1;
	case MIPI_DSI_FMT_RGB565:
		return DSI_RGB565_CONF1;
	default:
		DRM_DEBUG_DRIVER("MIPI color invalid, so we use rgb888\n");
	}
	return DSI_RGB888;
}