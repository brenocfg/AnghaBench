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
 unsigned char AMI_MASK ; 

__attribute__((used)) static inline short int alaw2linear(unsigned char alaw)
{
	int i;
	int seg;

	alaw ^= AMI_MASK;
	i = ((alaw & 0x0F) << 4) + 8 /* rounding error */;
	seg = (((int) alaw & 0x70) >> 4);
	if (seg)
		i = (i + 0x100) << (seg - 1);
	return (short int) ((alaw & 0x80)  ?  i  :  -i);
}