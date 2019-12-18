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
struct intel_crtc_state {int port_clock; } ;
struct bxt_clk_div {int clock; int vco; int p1; int p2; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bxt_clk_div*) ; 
 struct bxt_clk_div* bxt_dp_clk_val ; 

__attribute__((used)) static void bxt_ddi_dp_pll_dividers(struct intel_crtc_state *crtc_state,
				    struct bxt_clk_div *clk_div)
{
	int clock = crtc_state->port_clock;
	int i;

	*clk_div = bxt_dp_clk_val[0];
	for (i = 0; i < ARRAY_SIZE(bxt_dp_clk_val); ++i) {
		if (bxt_dp_clk_val[i].clock == clock) {
			*clk_div = bxt_dp_clk_val[i];
			break;
		}
	}

	clk_div->vco = clock * 10 / 2 * clk_div->p1 * clk_div->p2;
}