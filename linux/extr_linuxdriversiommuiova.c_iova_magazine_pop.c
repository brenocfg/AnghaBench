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
struct iova_magazine {int size; unsigned long* pfns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iova_magazine_empty (struct iova_magazine*) ; 

__attribute__((used)) static unsigned long iova_magazine_pop(struct iova_magazine *mag,
				       unsigned long limit_pfn)
{
	int i;
	unsigned long pfn;

	BUG_ON(iova_magazine_empty(mag));

	/* Only fall back to the rbtree if we have no suitable pfns at all */
	for (i = mag->size - 1; mag->pfns[i] > limit_pfn; i--)
		if (i == 0)
			return 0;

	/* Swap it to pop it */
	pfn = mag->pfns[i];
	mag->pfns[i] = mag->pfns[--mag->size];

	return pfn;
}