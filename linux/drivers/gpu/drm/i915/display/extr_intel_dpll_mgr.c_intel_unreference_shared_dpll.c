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
struct intel_shared_dpll_state {int crtc_mask; } ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct intel_crtc {int pipe; } ;
struct intel_atomic_state {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {size_t id; } ;

/* Variables and functions */
 struct intel_shared_dpll_state* intel_atomic_get_shared_dpll_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_unreference_shared_dpll(struct intel_atomic_state *state,
					  const struct intel_crtc *crtc,
					  const struct intel_shared_dpll *pll)
{
	struct intel_shared_dpll_state *shared_dpll;

	shared_dpll = intel_atomic_get_shared_dpll_state(&state->base);
	shared_dpll[pll->info->id].crtc_mask &= ~(1 << crtc->pipe);
}