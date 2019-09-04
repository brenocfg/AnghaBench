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
 scalar_t__ gdb_vbr_vector ; 

void sh_bios_vbr_reload(void)
{
	if (gdb_vbr_vector)
		__asm__ __volatile__ (
			"ldc %0, vbr"
			:
			: "r" (((unsigned long) gdb_vbr_vector) - 0x100)
			: "memory"
		);
}