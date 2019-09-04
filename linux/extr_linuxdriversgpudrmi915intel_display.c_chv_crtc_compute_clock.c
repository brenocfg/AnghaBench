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
struct intel_limit {int dummy; } ;
struct intel_crtc_state {int /*<<< orphan*/  dpll; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  clock_set; int /*<<< orphan*/  dpll_hw_state; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  chv_compute_dpll (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  chv_find_best_dpll (struct intel_limit const*,struct intel_crtc_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct intel_limit intel_limits_chv ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int chv_crtc_compute_clock(struct intel_crtc *crtc,
				  struct intel_crtc_state *crtc_state)
{
	int refclk = 100000;
	const struct intel_limit *limit = &intel_limits_chv;

	memset(&crtc_state->dpll_hw_state, 0,
	       sizeof(crtc_state->dpll_hw_state));

	if (!crtc_state->clock_set &&
	    !chv_find_best_dpll(limit, crtc_state, crtc_state->port_clock,
				refclk, NULL, &crtc_state->dpll)) {
		DRM_ERROR("Couldn't find PLL settings for mode!\n");
		return -EINVAL;
	}

	chv_compute_dpll(crtc, crtc_state);

	return 0;
}