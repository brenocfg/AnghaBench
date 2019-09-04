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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

void uvc_simplify_fraction(u32 *numerator, u32 *denominator,
		unsigned int n_terms, unsigned int threshold)
{
	u32 *an;
	u32 x, y, r;
	unsigned int i, n;

	an = kmalloc_array(n_terms, sizeof(*an), GFP_KERNEL);
	if (an == NULL)
		return;

	/* Convert the fraction to a simple continued fraction. See
	 * http://mathforum.org/dr.math/faq/faq.fractions.html
	 * Stop if the current term is bigger than or equal to the given
	 * threshold.
	 */
	x = *numerator;
	y = *denominator;

	for (n = 0; n < n_terms && y != 0; ++n) {
		an[n] = x / y;
		if (an[n] >= threshold) {
			if (n < 2)
				n++;
			break;
		}

		r = x - an[n] * y;
		x = y;
		y = r;
	}

	/* Expand the simple continued fraction back to an integer fraction. */
	x = 0;
	y = 1;

	for (i = n; i > 0; --i) {
		r = y;
		y = an[i-1] * y + x;
		x = r;
	}

	*numerator = y;
	*denominator = x;
	kfree(an);
}