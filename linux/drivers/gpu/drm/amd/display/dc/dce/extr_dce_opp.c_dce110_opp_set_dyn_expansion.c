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
struct output_pixel_processor {int dummy; } ;
struct dce110_opp {int dummy; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 130 
#define  COLOR_DEPTH_121212 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  FMT_DYNAMIC_EXP_CNTL ; 
 int /*<<< orphan*/  FMT_DYNAMIC_EXP_EN ; 
 int /*<<< orphan*/  FMT_DYNAMIC_EXP_MODE ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int SIGNAL_TYPE_DISPLAY_PORT ; 
 int SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 
 struct dce110_opp* TO_DCE110_OPP (struct output_pixel_processor*) ; 

void dce110_opp_set_dyn_expansion(
	struct output_pixel_processor *opp,
	enum dc_color_space color_sp,
	enum dc_color_depth color_dpth,
	enum signal_type signal)
{
	struct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
			FMT_DYNAMIC_EXP_EN, 0,
			FMT_DYNAMIC_EXP_MODE, 0);

	/*00 - 10-bit -> 12-bit dynamic expansion*/
	/*01 - 8-bit  -> 12-bit dynamic expansion*/
	if (signal == SIGNAL_TYPE_HDMI_TYPE_A ||
		signal == SIGNAL_TYPE_DISPLAY_PORT ||
		signal == SIGNAL_TYPE_DISPLAY_PORT_MST) {
		switch (color_dpth) {
		case COLOR_DEPTH_888:
			REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,
				FMT_DYNAMIC_EXP_MODE, 1);
			break;
		case COLOR_DEPTH_101010:
			REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,
				FMT_DYNAMIC_EXP_MODE, 0);
			break;
		case COLOR_DEPTH_121212:
			REG_UPDATE_2(
				FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,/*otherwise last two bits are zero*/
				FMT_DYNAMIC_EXP_MODE, 0);
			break;
		default:
			break;
		}
	}
}