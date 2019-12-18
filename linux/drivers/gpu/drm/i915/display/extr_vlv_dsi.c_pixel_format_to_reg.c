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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mipi_dsi_pixel_format { ____Placeholder_mipi_dsi_pixel_format } mipi_dsi_pixel_format ;

/* Variables and functions */
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  VID_MODE_FORMAT_RGB565 ; 
 int /*<<< orphan*/  VID_MODE_FORMAT_RGB666 ; 
 int /*<<< orphan*/  VID_MODE_FORMAT_RGB666_PACKED ; 
 int /*<<< orphan*/  VID_MODE_FORMAT_RGB888 ; 

__attribute__((used)) static u32 pixel_format_to_reg(enum mipi_dsi_pixel_format fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_RGB888:
		return VID_MODE_FORMAT_RGB888;
	case MIPI_DSI_FMT_RGB666:
		return VID_MODE_FORMAT_RGB666;
	case MIPI_DSI_FMT_RGB666_PACKED:
		return VID_MODE_FORMAT_RGB666_PACKED;
	case MIPI_DSI_FMT_RGB565:
		return VID_MODE_FORMAT_RGB565;
	default:
		MISSING_CASE(fmt);
		return VID_MODE_FORMAT_RGB666;
	}
}