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
struct s390_idle_data {unsigned long long clock_idle_exit; unsigned long long clock_idle_enter; unsigned long long idle_time; int /*<<< orphan*/  seqcount; int /*<<< orphan*/  idle_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_NOHZ_DELAY ; 
 unsigned long PSW_KERNEL_BITS ; 
 unsigned long PSW_MASK_DAT ; 
 unsigned long PSW_MASK_EXT ; 
 unsigned long PSW_MASK_IO ; 
 unsigned long PSW_MASK_MCHECK ; 
 unsigned long PSW_MASK_WAIT ; 
 int /*<<< orphan*/  account_idle_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_cpu_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_nsecs (unsigned long long) ; 
 int /*<<< orphan*/  psw_idle (struct s390_idle_data*,unsigned long) ; 
 int /*<<< orphan*/  s390_idle ; 
 struct s390_idle_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hardirqs_off () ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

void enabled_wait(void)
{
	struct s390_idle_data *idle = this_cpu_ptr(&s390_idle);
	unsigned long long idle_time;
	unsigned long psw_mask;

	trace_hardirqs_on();

	/* Wait for external, I/O or machine check interrupt. */
	psw_mask = PSW_KERNEL_BITS | PSW_MASK_WAIT | PSW_MASK_DAT |
		PSW_MASK_IO | PSW_MASK_EXT | PSW_MASK_MCHECK;
	clear_cpu_flag(CIF_NOHZ_DELAY);

	/* Call the assembler magic in entry.S */
	psw_idle(idle, psw_mask);

	trace_hardirqs_off();

	/* Account time spent with enabled wait psw loaded as idle time. */
	write_seqcount_begin(&idle->seqcount);
	idle_time = idle->clock_idle_exit - idle->clock_idle_enter;
	idle->clock_idle_enter = idle->clock_idle_exit = 0ULL;
	idle->idle_time += idle_time;
	idle->idle_count++;
	account_idle_time(cputime_to_nsecs(idle_time));
	write_seqcount_end(&idle->seqcount);
}