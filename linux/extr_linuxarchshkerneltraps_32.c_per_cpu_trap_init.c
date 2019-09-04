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
 int /*<<< orphan*/  clear_bl_bit () ; 

void per_cpu_trap_init(void)
{
	extern void *vbr_base;

	/* NOTE: The VBR value should be at P1
	   (or P2, virtural "fixed" address space).
	   It's definitely should not in physical address.  */

	asm volatile("ldc	%0, vbr"
		     : /* no output */
		     : "r" (&vbr_base)
		     : "memory");

	/* disable exception blocking now when the vbr has been setup */
	clear_bl_bit();
}