#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t id; } ;
struct mm_struct {TYPE_2__ context; } ;
struct TYPE_3__ {scalar_t__ prtb0; } ;

/* Variables and functions */
 size_t MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_contexts (TYPE_2__*) ; 
 TYPE_1__* process_tb ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  subpage_prot_free (struct mm_struct*) ; 

void destroy_context(struct mm_struct *mm)
{
#ifdef CONFIG_SPAPR_TCE_IOMMU
	WARN_ON_ONCE(!list_empty(&mm->context.iommu_group_mem_list));
#endif
	if (radix_enabled())
		WARN_ON(process_tb[mm->context.id].prtb0 != 0);
	else
		subpage_prot_free(mm);
	destroy_contexts(&mm->context);
	mm->context.id = MMU_NO_CONTEXT;
}