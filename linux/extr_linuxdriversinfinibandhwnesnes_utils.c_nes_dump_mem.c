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
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PFX ; 
 int /*<<< orphan*/  nes_debug (unsigned int,char*,void*,int,...) ; 
 unsigned int nes_debug_level ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void*,int,int) ; 

void nes_dump_mem(unsigned int dump_debug_level, void *addr, int length)
{
	if (!(nes_debug_level & dump_debug_level)) {
		return;
	}

	if (length > 0x100) {
		nes_debug(dump_debug_level, "Length truncated from %x to %x\n", length, 0x100);
		length = 0x100;
	}
	nes_debug(dump_debug_level, "Address=0x%p, length=0x%x (%d)\n", addr, length, length);

	print_hex_dump(KERN_ERR, PFX, DUMP_PREFIX_NONE, 16, 1, addr, length, true);
}