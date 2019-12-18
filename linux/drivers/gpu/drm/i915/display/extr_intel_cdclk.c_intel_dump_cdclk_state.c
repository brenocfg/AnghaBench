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
struct intel_cdclk_state {int /*<<< orphan*/  voltage_level; int /*<<< orphan*/  bypass; int /*<<< orphan*/  ref; int /*<<< orphan*/  vco; int /*<<< orphan*/  cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_dump_cdclk_state(const struct intel_cdclk_state *cdclk_state,
			    const char *context)
{
	DRM_DEBUG_DRIVER("%s %d kHz, VCO %d kHz, ref %d kHz, bypass %d kHz, voltage level %d\n",
			 context, cdclk_state->cdclk, cdclk_state->vco,
			 cdclk_state->ref, cdclk_state->bypass,
			 cdclk_state->voltage_level);
}