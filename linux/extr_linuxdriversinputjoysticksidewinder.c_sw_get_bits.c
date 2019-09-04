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
typedef  int __u64 ;

/* Variables and functions */

__attribute__((used)) static __u64 sw_get_bits(unsigned char *buf, int pos, int num, char bits)
{
	__u64 data = 0;
	int tri = pos % bits;						/* Start position */
	int i   = pos / bits;
	int bit = 0;

	while (num--) {
		data |= (__u64)((buf[i] >> tri++) & 1) << bit++;	/* Transfer bit */
		if (tri == bits) {
			i++;						/* Next triplet */
			tri = 0;
		}
	}

	return data;
}