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
struct intel_shared_dpll_state {int crtc_mask; int /*<<< orphan*/  hw_state; } ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {struct intel_shared_dpll* shared_dpll; int /*<<< orphan*/  dpll_hw_state; TYPE_2__ base; } ;
struct intel_crtc {int pipe; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_3__ {int id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_shared_dpll_state* intel_atomic_get_shared_dpll_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_reference_shared_dpll(struct intel_shared_dpll *pll,
			    struct intel_crtc_state *crtc_state)
{
	struct intel_shared_dpll_state *shared_dpll;
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	const enum intel_dpll_id id = pll->info->id;

	shared_dpll = intel_atomic_get_shared_dpll_state(crtc_state->base.state);

	if (shared_dpll[id].crtc_mask == 0)
		shared_dpll[id].hw_state =
			crtc_state->dpll_hw_state;

	crtc_state->shared_dpll = pll;
	DRM_DEBUG_DRIVER("using %s for pipe %c\n", pll->info->name,
			 pipe_name(crtc->pipe));

	shared_dpll[id].crtc_mask |= 1 << crtc->pipe;
}