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
 int /*<<< orphan*/  DSI_24BITS_1 ; 
#define  MIPI_DSI_FMT_RGB888 128 

__attribute__((used)) static u32 dsi_get_dpi_color_coding(enum mipi_dsi_pixel_format format)
{
	u32 val;

	/*
	 * TODO: only support RGB888 now, to support more
	 */
	switch (format) {
	case MIPI_DSI_FMT_RGB888:
		val = DSI_24BITS_1;
		break;
	default:
		val = DSI_24BITS_1;
		break;
	}

	return val;
}