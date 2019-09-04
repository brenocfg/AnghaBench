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
 int DIV_ROUND_CLOSEST (int,int) ; 
 int mipi_dsi_pixel_format_to_bpp (int) ; 

__attribute__((used)) static u32 dsi_clk_from_pclk(u32 pclk, enum mipi_dsi_pixel_format fmt,
			     int lane_count)
{
	u32 dsi_clk_khz;
	u32 bpp = mipi_dsi_pixel_format_to_bpp(fmt);

	/* DSI data rate = pixel clock * bits per pixel / lane count
	   pixel clock is converted from KHz to Hz */
	dsi_clk_khz = DIV_ROUND_CLOSEST(pclk * bpp, lane_count);

	return dsi_clk_khz;
}