#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct s390_idle_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ clock_comparator; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_IGNORE_IRQ ; 
 unsigned long CR0_IRQ_SUBCLASS_MASK ; 
 unsigned long PSW_MASK_EXT ; 
 unsigned long PSW_MASK_WAIT ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __ctl_load (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long __extract_psw () ; 
 int /*<<< orphan*/  clear_cpu_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ get_tod_clock () ; 
 int /*<<< orphan*/  psw_idle (struct s390_idle_data*,unsigned long) ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 
 int /*<<< orphan*/  set_cpu_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __udelay_disabled(unsigned long long usecs)
{
	unsigned long cr0, cr0_new, psw_mask;
	struct s390_idle_data idle;
	u64 end;

	end = get_tod_clock() + (usecs << 12);
	__ctl_store(cr0, 0, 0);
	cr0_new = cr0 & ~CR0_IRQ_SUBCLASS_MASK;
	cr0_new |= (1UL << (63 - 52)); /* enable clock comparator irq */
	__ctl_load(cr0_new, 0, 0);
	psw_mask = __extract_psw() | PSW_MASK_EXT | PSW_MASK_WAIT;
	set_clock_comparator(end);
	set_cpu_flag(CIF_IGNORE_IRQ);
	psw_idle(&idle, psw_mask);
	clear_cpu_flag(CIF_IGNORE_IRQ);
	set_clock_comparator(S390_lowcore.clock_comparator);
	__ctl_load(cr0, 0, 0);
}