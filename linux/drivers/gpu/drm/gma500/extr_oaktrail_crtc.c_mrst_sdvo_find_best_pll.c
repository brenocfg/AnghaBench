#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int max; int min; } ;
struct TYPE_9__ {int p2_slow; } ;
struct TYPE_8__ {int min; int max; } ;
struct TYPE_7__ {int min; int max; } ;
struct TYPE_6__ {int min; int max; } ;
struct gma_limit_t {TYPE_5__ vco; TYPE_4__ p2; TYPE_3__ p1; TYPE_2__ n; TYPE_1__ m; } ;
struct gma_clock_t {int m; int n; int p1; int p; } ;
struct drm_crtc {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct gma_clock_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mrst_sdvo_find_best_pll(const struct gma_limit_t *limit,
				    struct drm_crtc *crtc, int target,
				    int refclk, struct gma_clock_t *best_clock)
{
	struct gma_clock_t clock;
	u32 target_vco, actual_freq;
	s32 freq_error, min_error = 100000;

	memset(best_clock, 0, sizeof(*best_clock));

	for (clock.m = limit->m.min; clock.m <= limit->m.max; clock.m++) {
		for (clock.n = limit->n.min; clock.n <= limit->n.max;
		     clock.n++) {
			for (clock.p1 = limit->p1.min;
			     clock.p1 <= limit->p1.max; clock.p1++) {
				/* p2 value always stored in p2_slow on SDVO */
				clock.p = clock.p1 * limit->p2.p2_slow;
				target_vco = target * clock.p;

				/* VCO will increase at this point so break */
				if (target_vco > limit->vco.max)
					break;

				if (target_vco < limit->vco.min)
					continue;

				actual_freq = (refclk * clock.m) /
					      (clock.n * clock.p);
				freq_error = 10000 -
					     ((target * 10000) / actual_freq);

				if (freq_error < -min_error) {
					/* freq_error will start to decrease at
					   this point so break */
					break;
				}

				if (freq_error < 0)
					freq_error = -freq_error;

				if (freq_error < min_error) {
					min_error = freq_error;
					*best_clock = clock;
				}
			}
		}
		if (min_error == 0)
			break;
	}

	return min_error == 0;
}