#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_11__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_10__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_9__ {scalar_t__ min; scalar_t__ max; } ;
struct intel_limit {TYPE_6__ p1; TYPE_5__ n; TYPE_4__ m2; TYPE_3__ m1; } ;
struct TYPE_8__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
struct dpll {scalar_t__ m1; scalar_t__ m2; scalar_t__ n; scalar_t__ p1; scalar_t__ p; scalar_t__ dot; int /*<<< orphan*/  p2; } ;
struct TYPE_7__ {struct drm_device* dev; } ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  i9xx_calc_dpll_params (int,struct dpll*) ; 
 int /*<<< orphan*/  i9xx_select_p2_div (struct intel_limit const*,struct intel_crtc_state*,int) ; 
 int /*<<< orphan*/  intel_PLL_is_valid (int /*<<< orphan*/ ,struct intel_limit const*,struct dpll*) ; 
 int /*<<< orphan*/  memset (struct dpll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_i915 (struct drm_device*) ; 

__attribute__((used)) static bool
i9xx_find_best_dpll(const struct intel_limit *limit,
		    struct intel_crtc_state *crtc_state,
		    int target, int refclk, struct dpll *match_clock,
		    struct dpll *best_clock)
{
	struct drm_device *dev = crtc_state->base.crtc->dev;
	struct dpll clock;
	int err = target;

	memset(best_clock, 0, sizeof(*best_clock));

	clock.p2 = i9xx_select_p2_div(limit, crtc_state, target);

	for (clock.m1 = limit->m1.min; clock.m1 <= limit->m1.max;
	     clock.m1++) {
		for (clock.m2 = limit->m2.min;
		     clock.m2 <= limit->m2.max; clock.m2++) {
			if (clock.m2 >= clock.m1)
				break;
			for (clock.n = limit->n.min;
			     clock.n <= limit->n.max; clock.n++) {
				for (clock.p1 = limit->p1.min;
					clock.p1 <= limit->p1.max; clock.p1++) {
					int this_err;

					i9xx_calc_dpll_params(refclk, &clock);
					if (!intel_PLL_is_valid(to_i915(dev),
								limit,
								&clock))
						continue;
					if (match_clock &&
					    clock.p != match_clock->p)
						continue;

					this_err = abs(clock.dot - target);
					if (this_err < err) {
						*best_clock = clock;
						err = this_err;
					}
				}
			}
		}
	}

	return (err != target);
}