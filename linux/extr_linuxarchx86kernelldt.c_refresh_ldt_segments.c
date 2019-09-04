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

__attribute__((used)) static void refresh_ldt_segments(void)
{
#ifdef CONFIG_X86_64
	unsigned short sel;

	/*
	 * Make sure that the cached DS and ES descriptors match the updated
	 * LDT.
	 */
	savesegment(ds, sel);
	if ((sel & SEGMENT_TI_MASK) == SEGMENT_LDT)
		loadsegment(ds, sel);

	savesegment(es, sel);
	if ((sel & SEGMENT_TI_MASK) == SEGMENT_LDT)
		loadsegment(es, sel);
#endif
}