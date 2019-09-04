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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static void srl128(u64 *hptr, u64 *lptr, int count)
{
	u64 low;

	if (count >= 128) {
		*lptr = *hptr != 0 || *lptr != 0;
		*hptr = 0;
	} else if (count >= 64) {
		if (count == 64) {
			*lptr = *hptr | (*lptr != 0);
		} else {
			low = *lptr;
			*lptr = *hptr >> (count - 64);
			*lptr |= (*hptr << (128 - count)) != 0 || low != 0;
		}
		*hptr = 0;
	} else {
		low = *lptr;
		*lptr = low >> count | *hptr << (64 - count);
		*lptr |= (low << (64 - count)) != 0;
		*hptr = *hptr >> count;
	}
}