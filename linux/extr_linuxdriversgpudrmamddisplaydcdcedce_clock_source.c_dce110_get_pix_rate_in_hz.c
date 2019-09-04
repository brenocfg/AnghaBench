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
struct pll_settings {int dummy; } ;
struct pixel_clk_params {int signal_type; } ;
struct clock_source {int dummy; } ;

/* Variables and functions */
#define  SIGNAL_TYPE_DISPLAY_PORT 132 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 131 
#define  SIGNAL_TYPE_EDP 130 
#define  SIGNAL_TYPE_HDMI_TYPE_A 129 
#define  SIGNAL_TYPE_VIRTUAL 128 
 int /*<<< orphan*/  dce110_get_d_to_pixel_rate_in_hz (struct clock_source*,struct pixel_clk_params*,struct pll_settings*) ; 
 int /*<<< orphan*/  dce110_get_pll_pixel_rate_in_hz (struct clock_source*,struct pixel_clk_params*,struct pll_settings*) ; 

__attribute__((used)) static uint32_t dce110_get_pix_rate_in_hz(
	struct clock_source *cs,
	struct pixel_clk_params *pix_clk_params,
	struct pll_settings *pll_settings)
{
	uint32_t pix_rate = 0;
	switch (pix_clk_params->signal_type) {
	case	SIGNAL_TYPE_DISPLAY_PORT:
	case	SIGNAL_TYPE_DISPLAY_PORT_MST:
	case	SIGNAL_TYPE_EDP:
	case	SIGNAL_TYPE_VIRTUAL:
		pix_rate = dce110_get_d_to_pixel_rate_in_hz(cs, pix_clk_params, pll_settings);
		break;
	case	SIGNAL_TYPE_HDMI_TYPE_A:
	default:
		pix_rate = dce110_get_pll_pixel_rate_in_hz(cs, pix_clk_params, pll_settings);
		break;
	}

	return pix_rate;
}