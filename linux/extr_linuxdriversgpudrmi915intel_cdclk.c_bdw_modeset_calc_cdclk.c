#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cdclk; void* voltage_level; } ;
struct TYPE_4__ {TYPE_1__ logical; TYPE_1__ actual; } ;
struct intel_atomic_state {TYPE_2__ cdclk; int /*<<< orphan*/  active_crtcs; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int bdw_calc_cdclk (int) ; 
 void* bdw_calc_voltage_level (int) ; 
 int intel_compute_min_cdclk (struct drm_atomic_state*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 

__attribute__((used)) static int bdw_modeset_calc_cdclk(struct drm_atomic_state *state)
{
	struct intel_atomic_state *intel_state = to_intel_atomic_state(state);
	int min_cdclk, cdclk;

	min_cdclk = intel_compute_min_cdclk(state);
	if (min_cdclk < 0)
		return min_cdclk;

	/*
	 * FIXME should also account for plane ratio
	 * once 64bpp pixel formats are supported.
	 */
	cdclk = bdw_calc_cdclk(min_cdclk);

	intel_state->cdclk.logical.cdclk = cdclk;
	intel_state->cdclk.logical.voltage_level =
		bdw_calc_voltage_level(cdclk);

	if (!intel_state->active_crtcs) {
		cdclk = bdw_calc_cdclk(0);

		intel_state->cdclk.actual.cdclk = cdclk;
		intel_state->cdclk.actual.voltage_level =
			bdw_calc_voltage_level(cdclk);
	} else {
		intel_state->cdclk.actual =
			intel_state->cdclk.logical;
	}

	return 0;
}