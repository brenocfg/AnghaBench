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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int __kernel_size_t ;

/* Variables and functions */

void *memcpy(void *dest, __const void *src, __kernel_size_t n)
{
	unsigned char *d = (unsigned char *)dest, *s = (unsigned char *)src;
	uint32_t *dest_w = (uint32_t *)dest, *src_w = (uint32_t *)src;

	/* If both source and dest are word aligned copy words */
	if (!((unsigned int)dest_w & 3) && !((unsigned int)src_w & 3)) {
		for (; n >= 4; n -= 4)
			*dest_w++ = *src_w++;
	}

	d = (unsigned char *)dest_w;
	s = (unsigned char *)src_w;

	/* For remaining or if not aligned, copy bytes */
	for (; n >= 1; n -= 1)
		*d++ = *s++;

	return dest;

}