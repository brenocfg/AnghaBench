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
 unsigned long BIT (int) ; 
 int BITS_PER_LONG ; 
 int ffs (unsigned long) ; 

int mt76_wcid_alloc(unsigned long *mask, int size)
{
	int i, idx = 0, cur;

	for (i = 0; i < size / BITS_PER_LONG; i++) {
		idx = ffs(~mask[i]);
		if (!idx)
			continue;

		idx--;
		cur = i * BITS_PER_LONG + idx;
		if (cur >= size)
			break;

		mask[i] |= BIT(idx);
		return cur;
	}

	return -1;
}