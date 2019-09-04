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

/* Variables and functions */
 int EINVAL ; 
 int TIMECODES ; 
 int abs (int) ; 
 int* time_codes ; 

__attribute__((used)) static int choose_times(int msec, int *c1p, int *c2p)
{
	/*
	 * Choose two timecodes which add to 'msec' as near as
	 * possible.  The first returned is the 'on' or 'off' time.
	 * The second is to be used as a 'fade-on' or 'fade-off' time.
	 * If 'msec' is even, the first will not be smaller than the
	 * second.  If 'msec' is odd, the first will not be larger
	 * than the second.
	 * If we cannot get a sum within 1/8 of 'msec' fail with
	 * -EINVAL, otherwise return the sum that was achieved, plus 1
	 * if the first is smaller.
	 * If two possibilities are equally good (e.g. 512+0,
	 * 256+256), choose the first pair so there is more
	 * change-time visible (i.e. it is softer).
	 */
	int c1, c2;
	int tmax = msec * 9 / 8;
	int tmin = msec * 7 / 8;
	int diff = 65536;

	/* We start at '1' to ensure we never even think of choosing a
	 * total time of '0'.
	 */
	for (c1 = 1; c1 < TIMECODES; c1++) {
		int t = time_codes[c1];
		if (t*2 < tmin)
			continue;
		if (t > tmax)
			break;
		for (c2 = 0; c2 <= c1; c2++) {
			int tt = t + time_codes[c2];
			int d;
			if (tt < tmin)
				continue;
			if (tt > tmax)
				break;
			/* This works! */
			d = abs(msec - tt);
			if (d >= diff)
				continue;
			/* Best yet */
			*c1p = c1;
			*c2p = c2;
			diff = d;
			if (d == 0)
				return msec;
		}
	}
	if (diff < 65536) {
		int actual;
		if (msec & 1) {
			c1 = *c2p;
			*c2p = *c1p;
			*c1p = c1;
		}
		actual = time_codes[*c1p] + time_codes[*c2p];
		if (*c1p < *c2p)
			return actual + 1;
		else
			return actual;
	}
	/* No close match */
	return -EINVAL;
}