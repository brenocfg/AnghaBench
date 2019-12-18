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

__attribute__((used)) static int adjust_dual(int *begin, int step, int *end, int eq, int mu)
{
	int f, *p, s, c;

	if (begin == end)
		return 0;

	f = *begin;
	p = begin + step;
	s = p == end ? f + 1 : *p;

	for (; p != end; p += step)
		if (*p < f)
			s = f, f = *p;
		else if (*p < s)
			s = *p;

	c = (f + s + 1) / 2;
	if (c == 0 || (c > mu && (!eq || mu > 0)))
		return 0;
	/* Improve convergence for positive matrices by penalizing overcovers */
	if (s < 0 && mu <= 0)
		c *= 2;

	for (p = begin; p != end; p += step)
		*p -= c;

	return (c < s && s <= 0) || (f >= 0 && f < c);
}