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

__attribute__((used)) static bool is_shadowed_mmio(unsigned int offset)
{
	bool ret = false;

	if ((offset == 0x2168) || /*BB current head register UDW */
	    (offset == 0x2140) || /*BB current header register */
	    (offset == 0x211c) || /*second BB header register UDW */
	    (offset == 0x2114)) { /*second BB header register UDW */
		ret = true;
	}
	return ret;
}