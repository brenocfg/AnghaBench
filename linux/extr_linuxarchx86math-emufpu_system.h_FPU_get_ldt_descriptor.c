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
struct desc_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct desc_struct FPU_get_ldt_descriptor(unsigned seg)
{
	static struct desc_struct zero_desc;
	struct desc_struct ret = zero_desc;

#ifdef CONFIG_MODIFY_LDT_SYSCALL
	seg >>= 3;
	mutex_lock(&current->mm->context.lock);
	if (current->mm->context.ldt && seg < current->mm->context.ldt->nr_entries)
		ret = current->mm->context.ldt->entries[seg];
	mutex_unlock(&current->mm->context.lock);
#endif
	return ret;
}