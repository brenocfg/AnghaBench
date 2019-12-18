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
struct intel_dpll_hw_state {int dummy; } ;
struct intel_shared_dpll_state {int crtc_mask; struct intel_dpll_hw_state hw_state; } ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct intel_crtc {int pipe; } ;
struct intel_atomic_state {int /*<<< orphan*/  base; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_shared_dpll_state* intel_atomic_get_shared_dpll_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static void
intel_reference_shared_dpll(struct intel_atomic_state *state,
			    const struct intel_crtc *crtc,
			    const struct intel_shared_dpll *pll,
			    const struct intel_dpll_hw_state *pll_state)
{
	struct intel_shared_dpll_state *shared_dpll;
	const enum intel_dpll_id id = pll->info->id;

	shared_dpll = intel_atomic_get_shared_dpll_state(&state->base);

	if (shared_dpll[id].crtc_mask == 0)
		shared_dpll[id].hw_state = *pll_state;

	DRM_DEBUG_DRIVER("using %s for pipe %c\n", pll->info->name,
			 pipe_name(crtc->pipe));

	shared_dpll[id].crtc_mask |= 1 << crtc->pipe;
}