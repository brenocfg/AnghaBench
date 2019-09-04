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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static int kvm_vcpu_check_hw_bp(unsigned long addr, u32 type, u32 dr7,
				unsigned long *db)
{
	u32 dr6 = 0;
	int i;
	u32 enable, rwlen;

	enable = dr7;
	rwlen = dr7 >> 16;
	for (i = 0; i < 4; i++, enable >>= 2, rwlen >>= 4)
		if ((enable & 3) && (rwlen & 15) == type && db[i] == addr)
			dr6 |= (1 << i);
	return dr6;
}