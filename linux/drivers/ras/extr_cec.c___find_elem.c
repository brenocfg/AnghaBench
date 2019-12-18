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
typedef  int /*<<< orphan*/  u64 ;
struct ce_array {int n; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int ENOKEY ; 
 int /*<<< orphan*/  PFN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __find_elem(struct ce_array *ca, u64 pfn, unsigned int *to)
{
	int min = 0, max = ca->n - 1;
	u64 this_pfn;

	while (min <= max) {
		int i = (min + max) >> 1;

		this_pfn = PFN(ca->array[i]);

		if (this_pfn < pfn)
			min = i + 1;
		else if (this_pfn > pfn)
			max = i - 1;
		else if (this_pfn == pfn) {
			if (to)
				*to = i;

			return i;
		}
	}

	/*
	 * When the loop terminates without finding @pfn, min has the index of
	 * the element slot where the new @pfn should be inserted. The loop
	 * terminates when min > max, which means the min index points to the
	 * bigger element while the max index to the smaller element, in-between
	 * which the new @pfn belongs to.
	 *
	 * For more details, see exercise 1, Section 6.2.1 in TAOCP, vol. 3.
	 */
	if (to)
		*to = min;

	return -ENOKEY;
}