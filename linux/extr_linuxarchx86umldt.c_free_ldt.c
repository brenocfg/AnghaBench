#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* pages; } ;
struct TYPE_5__ {int entry_count; TYPE_1__ u; } ;
struct TYPE_6__ {TYPE_2__ ldt; } ;
struct mm_context {TYPE_3__ arch; } ;

/* Variables and functions */
 int LDT_DIRECT_ENTRIES ; 
 int LDT_ENTRIES_PER_PAGE ; 
 int /*<<< orphan*/  free_page (long) ; 

void free_ldt(struct mm_context *mm)
{
	int i;

	if (mm->arch.ldt.entry_count > LDT_DIRECT_ENTRIES) {
		i = mm->arch.ldt.entry_count / LDT_ENTRIES_PER_PAGE;
		while (i-- > 0)
			free_page((long) mm->arch.ldt.u.pages[i]);
	}
	mm->arch.ldt.entry_count = 0;
}