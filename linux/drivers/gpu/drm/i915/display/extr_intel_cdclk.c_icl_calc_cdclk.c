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
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int icl_calc_cdclk(int min_cdclk, unsigned int ref)
{
	static const int ranges_24[] = { 180000, 192000, 312000, 552000, 648000 };
	static const int ranges_19_38[] = { 172800, 192000, 307200, 556800, 652800 };
	const int *ranges;
	int len, i;

	switch (ref) {
	default:
		MISSING_CASE(ref);
		/* fall through */
	case 24000:
		ranges = ranges_24;
		len = ARRAY_SIZE(ranges_24);
		break;
	case 19200:
	case 38400:
		ranges = ranges_19_38;
		len = ARRAY_SIZE(ranges_19_38);
		break;
	}

	for (i = 0; i < len; i++) {
		if (min_cdclk <= ranges[i])
			return ranges[i];
	}

	WARN_ON(min_cdclk > ranges[len - 1]);
	return ranges[len - 1];
}