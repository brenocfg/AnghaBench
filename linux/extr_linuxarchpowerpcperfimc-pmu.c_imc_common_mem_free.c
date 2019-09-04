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
struct imc_pmu {TYPE_1__** attr_groups; } ;
struct TYPE_2__ {struct TYPE_2__* attrs; } ;

/* Variables and functions */
 size_t IMC_EVENT_ATTR ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void imc_common_mem_free(struct imc_pmu *pmu_ptr)
{
	if (pmu_ptr->attr_groups[IMC_EVENT_ATTR])
		kfree(pmu_ptr->attr_groups[IMC_EVENT_ATTR]->attrs);
	kfree(pmu_ptr->attr_groups[IMC_EVENT_ATTR]);
}