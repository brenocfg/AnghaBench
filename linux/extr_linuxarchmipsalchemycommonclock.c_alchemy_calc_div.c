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

__attribute__((used)) static long alchemy_calc_div(unsigned long rate, unsigned long prate,
			       int scale, int maxdiv, unsigned long *rv)
{
	long div1, div2;

	div1 = prate / rate;
	if ((prate / div1) > rate)
		div1++;

	if (scale == 2) {	/* only div-by-multiple-of-2 possible */
		if (div1 & 1)
			div1++;	/* stay <=prate */
	}

	div2 = (div1 / scale) - 1;	/* value to write to register */

	if (div2 > maxdiv)
		div2 = maxdiv;
	if (rv)
		*rv = div2;

	div1 = ((div2 + 1) * scale);
	return div1;
}