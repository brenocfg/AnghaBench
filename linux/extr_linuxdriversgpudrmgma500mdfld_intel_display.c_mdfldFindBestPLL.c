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
struct TYPE_4__ {scalar_t__ min; scalar_t__ max; } ;
struct TYPE_3__ {scalar_t__ min; scalar_t__ max; } ;
struct mrst_limit_t {TYPE_2__ p1; TYPE_1__ m; } ;
struct mrst_clock_t {scalar_t__ m; scalar_t__ p1; scalar_t__ dot; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  mdfld_clock (int,struct mrst_clock_t*) ; 
 struct mrst_limit_t* mdfld_limit (struct drm_crtc*) ; 
 int /*<<< orphan*/  memset (struct mrst_clock_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
mdfldFindBestPLL(struct drm_crtc *crtc, int target, int refclk,
		struct mrst_clock_t *best_clock)
{
	struct mrst_clock_t clock;
	const struct mrst_limit_t *limit = mdfld_limit(crtc);
	int err = target;

	memset(best_clock, 0, sizeof(*best_clock));

	for (clock.m = limit->m.min; clock.m <= limit->m.max; clock.m++) {
		for (clock.p1 = limit->p1.min; clock.p1 <= limit->p1.max;
		     clock.p1++) {
			int this_err;

			mdfld_clock(refclk, &clock);

			this_err = abs(clock.dot - target);
			if (this_err < err) {
				*best_clock = clock;
				err = this_err;
			}
		}
	}
	return err != target;
}