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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum as_signal_type { ____Placeholder_as_signal_type } as_signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_GPUPLL_SS ; 
 int /*<<< orphan*/  ASIC_INTERNAL_SS_ON_DP ; 
 int /*<<< orphan*/  ASIC_INTERNAL_SS_ON_HDMI ; 
 int /*<<< orphan*/  ASIC_INTERNAL_SS_ON_LVDS ; 
 int /*<<< orphan*/  ASIC_INTERNAL_SS_ON_TMDS ; 
#define  AS_SIGNAL_TYPE_DISPLAY_PORT 132 
#define  AS_SIGNAL_TYPE_DVI 131 
#define  AS_SIGNAL_TYPE_GPU_PLL 130 
#define  AS_SIGNAL_TYPE_HDMI 129 
#define  AS_SIGNAL_TYPE_LVDS 128 

__attribute__((used)) static uint32_t signal_to_ss_id(enum as_signal_type signal)
{
	uint32_t clk_id_ss = 0;

	switch (signal) {
	case AS_SIGNAL_TYPE_DVI:
		clk_id_ss = ASIC_INTERNAL_SS_ON_TMDS;
		break;
	case AS_SIGNAL_TYPE_HDMI:
		clk_id_ss = ASIC_INTERNAL_SS_ON_HDMI;
		break;
	case AS_SIGNAL_TYPE_LVDS:
		clk_id_ss = ASIC_INTERNAL_SS_ON_LVDS;
		break;
	case AS_SIGNAL_TYPE_DISPLAY_PORT:
		clk_id_ss = ASIC_INTERNAL_SS_ON_DP;
		break;
	case AS_SIGNAL_TYPE_GPU_PLL:
		clk_id_ss = ASIC_INTERNAL_GPUPLL_SS;
		break;
	default:
		break;
	}
	return clk_id_ss;
}