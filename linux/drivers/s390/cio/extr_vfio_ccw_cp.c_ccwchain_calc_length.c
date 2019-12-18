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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {scalar_t__ i2k; int /*<<< orphan*/  c64; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct channel_program {TYPE_2__ orb; struct ccw1* guest_cp; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int CCWCHAIN_LEN_MAX ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ccw_is_chain (struct ccw1*) ; 
 scalar_t__ ccw_is_idal (struct ccw1*) ; 
 int /*<<< orphan*/  is_tic_within_range (struct ccw1*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccwchain_calc_length(u64 iova, struct channel_program *cp)
{
	struct ccw1 *ccw = cp->guest_cp;
	int cnt = 0;

	do {
		cnt++;

		/*
		 * As we don't want to fail direct addressing even if the
		 * orb specified one of the unsupported formats, we defer
		 * checking for IDAWs in unsupported formats to here.
		 */
		if ((!cp->orb.cmd.c64 || cp->orb.cmd.i2k) && ccw_is_idal(ccw))
			return -EOPNOTSUPP;

		/*
		 * We want to keep counting if the current CCW has the
		 * command-chaining flag enabled, or if it is a TIC CCW
		 * that loops back into the current chain.  The latter
		 * is used for device orientation, where the CCW PRIOR to
		 * the TIC can either jump to the TIC or a CCW immediately
		 * after the TIC, depending on the results of its operation.
		 */
		if (!ccw_is_chain(ccw) && !is_tic_within_range(ccw, iova, cnt))
			break;

		ccw++;
	} while (cnt < CCWCHAIN_LEN_MAX + 1);

	if (cnt == CCWCHAIN_LEN_MAX + 1)
		cnt = -EINVAL;

	return cnt;
}