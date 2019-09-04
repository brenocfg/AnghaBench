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

__attribute__((used)) static void slice_flush_segments(void *parm)
{
#ifdef CONFIG_PPC64
	struct mm_struct *mm = parm;
	unsigned long flags;

	if (mm != current->active_mm)
		return;

	copy_mm_to_paca(current->active_mm);

	local_irq_save(flags);
	slb_flush_and_rebolt();
	local_irq_restore(flags);
#endif
}