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

__attribute__((used)) static unsigned long adjust_reg18(unsigned short data)
{
	unsigned long tmp1, tmp2;

	tmp1 = (data<<1 | 0x00000001) & 0x000001FF;
	tmp2 = (data<<2 | 0x00000200) & 0x0003FE00;
	return tmp1 | tmp2;
}