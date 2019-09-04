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
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 

__attribute__((used)) static int icl_calc_cdclk(int min_cdclk, unsigned int ref)
{
	int ranges_24[] = { 312000, 552000, 648000 };
	int ranges_19_38[] = { 307200, 556800, 652800 };
	int *ranges;

	switch (ref) {
	default:
		MISSING_CASE(ref);
		/* fall through */
	case 24000:
		ranges = ranges_24;
		break;
	case 19200:
	case 38400:
		ranges = ranges_19_38;
		break;
	}

	if (min_cdclk > ranges[1])
		return ranges[2];
	else if (min_cdclk > ranges[0])
		return ranges[1];
	else
		return ranges[0];
}