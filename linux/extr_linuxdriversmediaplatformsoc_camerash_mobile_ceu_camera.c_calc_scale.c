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
typedef  int u16 ;

/* Variables and functions */
 unsigned int size_dst (unsigned int,int) ; 

__attribute__((used)) static u16 calc_scale(unsigned int src, unsigned int *dst)
{
	u16 scale;

	if (src == *dst)
		return 0;

	scale = (src * 4096 / *dst) & ~7;

	while (scale > 4096 && size_dst(src, scale) < *dst)
		scale -= 8;

	*dst = size_dst(src, scale);

	return scale;
}