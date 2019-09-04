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
 int AMI_MASK ; 

__attribute__((used)) static inline unsigned char linear2alaw(short int linear)
{
	int mask;
	int seg;
	int pcm_val;
	static int seg_end[8] = {
		0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF
	};

	pcm_val = linear;
	if (pcm_val >= 0) {
		/* Sign (7th) bit = 1 */
		mask = AMI_MASK | 0x80;
	} else {
		/* Sign bit = 0 */
		mask = AMI_MASK;
		pcm_val = -pcm_val;
	}

	/* Convert the scaled magnitude to segment number. */
	for (seg = 0; seg < 8; seg++) {
		if (pcm_val <= seg_end[seg])
			break;
	}
	/* Combine the sign, segment, and quantization bits. */
	return  ((seg << 4) |
		 ((pcm_val >> ((seg)  ?  (seg + 3)  :  4)) & 0x0F)) ^ mask;
}