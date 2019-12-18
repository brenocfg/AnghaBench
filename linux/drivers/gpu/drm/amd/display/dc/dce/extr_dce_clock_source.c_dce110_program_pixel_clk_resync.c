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
struct dce110_clk_src {int dummy; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_161616 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  DCCG_DEEP_COLOR_CNTL1 ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESYNC_CNTL ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 

__attribute__((used)) static void dce110_program_pixel_clk_resync(
		struct dce110_clk_src *clk_src,
		enum signal_type signal_type,
		enum dc_color_depth colordepth)
{
	REG_UPDATE(RESYNC_CNTL,
			DCCG_DEEP_COLOR_CNTL1, 0);
	/*
	 24 bit mode: TMDS clock = 1.0 x pixel clock  (1:1)
	 30 bit mode: TMDS clock = 1.25 x pixel clock (5:4)
	 36 bit mode: TMDS clock = 1.5 x pixel clock  (3:2)
	 48 bit mode: TMDS clock = 2 x pixel clock    (2:1)
	 */
	if (signal_type != SIGNAL_TYPE_HDMI_TYPE_A)
		return;

	switch (colordepth) {
	case COLOR_DEPTH_888:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 0);
		break;
	case COLOR_DEPTH_101010:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 1);
		break;
	case COLOR_DEPTH_121212:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 2);
		break;
	case COLOR_DEPTH_161616:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 3);
		break;
	default:
		break;
	}
}