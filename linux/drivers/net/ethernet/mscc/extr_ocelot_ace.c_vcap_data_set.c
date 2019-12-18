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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ENTRY_WIDTH ; 

__attribute__((used)) static void vcap_data_set(u32 *data, u32 offset, u32 len, u32 value)
{
	u32 i, v, m;

	for (i = 0; i < len; i++, offset++) {
		v = data[offset / ENTRY_WIDTH];
		m = (1 << (offset % ENTRY_WIDTH));
		if (value & (1 << i))
			v |= m;
		else
			v &= ~m;
		data[offset / ENTRY_WIDTH] = v;
	}
}