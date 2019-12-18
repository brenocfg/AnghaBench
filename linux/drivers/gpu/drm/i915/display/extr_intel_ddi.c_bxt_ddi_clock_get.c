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
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int /*<<< orphan*/  dpll_hw_state; int /*<<< orphan*/  port_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_calc_pll_link (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddi_dotclock_get (struct intel_crtc_state*) ; 

__attribute__((used)) static void bxt_ddi_clock_get(struct intel_encoder *encoder,
			      struct intel_crtc_state *pipe_config)
{
	pipe_config->port_clock =
		bxt_calc_pll_link(&pipe_config->dpll_hw_state);

	ddi_dotclock_get(pipe_config);
}