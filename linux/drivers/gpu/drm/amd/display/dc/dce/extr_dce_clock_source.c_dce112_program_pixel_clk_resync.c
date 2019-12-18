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
typedef  int uint32_t ;
struct dce110_clk_src {TYPE_1__* cs_mask; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;
struct TYPE_2__ {scalar_t__ PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE; } ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_161616 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  PHYPLLA_DCCG_DEEP_COLOR_CNTL ; 
 int /*<<< orphan*/  PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE ; 
 int /*<<< orphan*/  PIXCLK_RESYNC_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 

__attribute__((used)) static void dce112_program_pixel_clk_resync(
		struct dce110_clk_src *clk_src,
		enum signal_type signal_type,
		enum dc_color_depth colordepth,
		bool enable_ycbcr420)
{
	uint32_t deep_color_cntl = 0;
	uint32_t double_rate_enable = 0;

	/*
	 24 bit mode: TMDS clock = 1.0 x pixel clock  (1:1)
	 30 bit mode: TMDS clock = 1.25 x pixel clock (5:4)
	 36 bit mode: TMDS clock = 1.5 x pixel clock  (3:2)
	 48 bit mode: TMDS clock = 2 x pixel clock    (2:1)
	 */
	if (signal_type == SIGNAL_TYPE_HDMI_TYPE_A) {
		double_rate_enable = enable_ycbcr420 ? 1 : 0;

		switch (colordepth) {
		case COLOR_DEPTH_888:
			deep_color_cntl = 0;
			break;
		case COLOR_DEPTH_101010:
			deep_color_cntl = 1;
			break;
		case COLOR_DEPTH_121212:
			deep_color_cntl = 2;
			break;
		case COLOR_DEPTH_161616:
			deep_color_cntl = 3;
			break;
		default:
			break;
		}
	}

	if (clk_src->cs_mask->PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE)
		REG_UPDATE_2(PIXCLK_RESYNC_CNTL,
				PHYPLLA_DCCG_DEEP_COLOR_CNTL, deep_color_cntl,
				PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE, double_rate_enable);
	else
		REG_UPDATE(PIXCLK_RESYNC_CNTL,
				PHYPLLA_DCCG_DEEP_COLOR_CNTL, deep_color_cntl);

}