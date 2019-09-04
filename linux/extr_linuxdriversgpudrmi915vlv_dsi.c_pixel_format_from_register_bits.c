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
typedef  int u32 ;
typedef  enum mipi_dsi_pixel_format { ____Placeholder_mipi_dsi_pixel_format } mipi_dsi_pixel_format ;

/* Variables and functions */
 int MIPI_DSI_FMT_RGB565 ; 
 int MIPI_DSI_FMT_RGB666 ; 
 int MIPI_DSI_FMT_RGB666_PACKED ; 
 int MIPI_DSI_FMT_RGB888 ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  VID_MODE_FORMAT_RGB565 131 
#define  VID_MODE_FORMAT_RGB666 130 
#define  VID_MODE_FORMAT_RGB666_PACKED 129 
#define  VID_MODE_FORMAT_RGB888 128 

enum mipi_dsi_pixel_format pixel_format_from_register_bits(u32 fmt)
{
	/* It just so happens the VBT matches register contents. */
	switch (fmt) {
	case VID_MODE_FORMAT_RGB888:
		return MIPI_DSI_FMT_RGB888;
	case VID_MODE_FORMAT_RGB666:
		return MIPI_DSI_FMT_RGB666;
	case VID_MODE_FORMAT_RGB666_PACKED:
		return MIPI_DSI_FMT_RGB666_PACKED;
	case VID_MODE_FORMAT_RGB565:
		return MIPI_DSI_FMT_RGB565;
	default:
		MISSING_CASE(fmt);
		return MIPI_DSI_FMT_RGB666;
	}
}