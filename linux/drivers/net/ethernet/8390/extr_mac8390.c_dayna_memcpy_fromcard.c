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
struct net_device {scalar_t__ mem_start; } ;

/* Variables and functions */

__attribute__((used)) static void dayna_memcpy_fromcard(struct net_device *dev, void *to, int from,
				  int count)
{
	volatile unsigned char *ptr;
	unsigned char *target = to;
	from <<= 1;	/* word, skip overhead */
	ptr = (unsigned char *)(dev->mem_start+from);
	/* Leading byte? */
	if (from & 2) {
		*target++ = ptr[-1];
		ptr += 2;
		count--;
	}
	while (count >= 2) {
		*(unsigned short *)target = *(unsigned short volatile *)ptr;
		ptr += 4;			/* skip cruft */
		target += 2;
		count -= 2;
	}
	/* Trailing byte? */
	if (count)
		*target = *ptr;
}