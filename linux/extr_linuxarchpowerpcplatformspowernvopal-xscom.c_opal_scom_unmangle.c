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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 opal_scom_unmangle(u64 addr)
{
	u64 tmp;

	/*
	 * XSCOM addresses use the top nibble to set indirect mode and
	 * its form.  Bits 4-11 are always 0.
	 *
	 * Because the debugfs interface uses signed offsets and shifts
	 * the address left by 3, we basically cannot use the top 4 bits
	 * of the 64-bit address, and thus cannot use the indirect bit.
	 *
	 * To deal with that, we support the indirect bits being in
	 * bits 4-7 (IBM notation) instead of bit 0-3 in this API, we
	 * do the conversion here.
	 *
	 * For in-kernel use, we don't need to do this mangling.  In
	 * kernel won't have bits 4-7 set.
	 *
	 * So:
	 *   debugfs will always   set 0-3 = 0 and clear 4-7
	 *    kernel will always clear 0-3 = 0 and   set 4-7
	 */
	tmp = addr;
	tmp  &= 0x0f00000000000000;
	addr &= 0xf0ffffffffffffff;
	addr |= tmp << 4;

	return addr;
}