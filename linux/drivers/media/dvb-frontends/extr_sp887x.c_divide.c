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

__attribute__((used)) static void divide (int n, int d, int *quotient_i, int *quotient_f)
{
	unsigned int q, r;

	r = (n % d) << 8;
	q = (r / d);

	if (quotient_i)
		*quotient_i = q;

	if (quotient_f) {
		r = (r % d) << 8;
		q = (q << 8) | (r / d);
		r = (r % d) << 8;
		*quotient_f = (q << 8) | (r / d);
	}
}