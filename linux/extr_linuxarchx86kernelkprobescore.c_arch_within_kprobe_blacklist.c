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
 scalar_t__ __entry_text_end ; 
 scalar_t__ __entry_text_start ; 
 scalar_t__ __kprobes_text_end ; 
 scalar_t__ __kprobes_text_start ; 

bool arch_within_kprobe_blacklist(unsigned long addr)
{
	bool is_in_entry_trampoline_section = false;

#ifdef CONFIG_X86_64
	is_in_entry_trampoline_section =
		(addr >= (unsigned long)__entry_trampoline_start &&
		 addr < (unsigned long)__entry_trampoline_end);
#endif
	return  (addr >= (unsigned long)__kprobes_text_start &&
		 addr < (unsigned long)__kprobes_text_end) ||
		(addr >= (unsigned long)__entry_text_start &&
		 addr < (unsigned long)__entry_text_end) ||
		is_in_entry_trampoline_section;
}