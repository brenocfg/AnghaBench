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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline void fill8_col(u8 *dst, u32 m[])
{
	u32 tmp = m[0];
	dst[0] = tmp;
	dst[2] = (tmp >>= 8);
#if BPL > 2
	dst[4] = (tmp >>= 8);
	dst[6] = tmp >> 8;
#endif
#if BPL > 4
	tmp = m[1];
	dst[8] = tmp;
	dst[10] = (tmp >>= 8);
	dst[12] = (tmp >>= 8);
	dst[14] = tmp >> 8;
#endif
}