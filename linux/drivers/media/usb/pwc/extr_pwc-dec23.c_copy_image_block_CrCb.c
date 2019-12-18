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
 void* CLAMP (int const) ; 
 int MAX_OUTER_CROP_VALUE ; 
 unsigned char* pwc_crop_table ; 

__attribute__((used)) static void copy_image_block_CrCb(const int *src, unsigned char *dst, unsigned int bytes_per_line, unsigned int scalebits)
{
#if UNROLL_LOOP_FOR_COPY
	/* Unroll all loops */
	const unsigned char *cm = pwc_crop_table+MAX_OUTER_CROP_VALUE;
	const int *c = src;
	unsigned char *d = dst;

	*d++ = cm[c[0] >> scalebits];
	*d++ = cm[c[4] >> scalebits];
	*d++ = cm[c[1] >> scalebits];
	*d++ = cm[c[5] >> scalebits];
	*d++ = cm[c[2] >> scalebits];
	*d++ = cm[c[6] >> scalebits];
	*d++ = cm[c[3] >> scalebits];
	*d++ = cm[c[7] >> scalebits];

	d = dst + bytes_per_line;
	*d++ = cm[c[12] >> scalebits];
	*d++ = cm[c[8] >> scalebits];
	*d++ = cm[c[13] >> scalebits];
	*d++ = cm[c[9] >> scalebits];
	*d++ = cm[c[14] >> scalebits];
	*d++ = cm[c[10] >> scalebits];
	*d++ = cm[c[15] >> scalebits];
	*d++ = cm[c[11] >> scalebits];
#else
	int i;
	const int *c1 = src;
	const int *c2 = src + 4;
	unsigned char *d = dst;

	for (i = 0; i < 4; i++, c1++, c2++) {
		*d++ = CLAMP((*c1) >> scalebits);
		*d++ = CLAMP((*c2) >> scalebits);
	}
	c1 = src + 12;
	d = dst + bytes_per_line;
	for (i = 0; i < 4; i++, c1++, c2++) {
		*d++ = CLAMP((*c1) >> scalebits);
		*d++ = CLAMP((*c2) >> scalebits);
	}
#endif
}