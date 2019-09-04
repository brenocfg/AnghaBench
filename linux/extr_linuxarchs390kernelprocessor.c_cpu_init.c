#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cpuid {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; int /*<<< orphan*/ * active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_3__ cpu_info ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  enter_lazy_tlb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  get_cpu_id (struct cpuid*) ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ machine_has_cpu_mhz ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ *) ; 
 struct cpuid* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_cpu_mhz (int /*<<< orphan*/ *) ; 

void cpu_init(void)
{
	struct cpuid *id = this_cpu_ptr(&cpu_info.cpu_id);

	get_cpu_id(id);
	if (machine_has_cpu_mhz)
		update_cpu_mhz(NULL);
	mmgrab(&init_mm);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);
	enter_lazy_tlb(&init_mm, current);
}