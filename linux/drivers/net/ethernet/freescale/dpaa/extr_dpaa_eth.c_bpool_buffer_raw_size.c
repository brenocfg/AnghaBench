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
typedef  int u8 ;

/* Variables and functions */
 int DPAA_BP_RAW_SIZE ; 

__attribute__((used)) static inline size_t bpool_buffer_raw_size(u8 index, u8 cnt)
{
	size_t res = DPAA_BP_RAW_SIZE / 4;
	u8 i;

	for (i = (cnt < 3) ? cnt : 3; i < 3 + index; i++)
		res *= 2;
	return res;
}