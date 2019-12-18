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
struct gen_pool {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pm_functions; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* emif_instance ; 
 void* sram_exec_copy (struct gen_pool*,void*,int /*<<< orphan*/ *,int) ; 

int ti_emif_copy_pm_function_table(struct gen_pool *sram_pool, void *dst)
{
	void *copy_addr;

	if (!emif_instance)
		return -ENODEV;

	copy_addr = sram_exec_copy(sram_pool, dst,
				   &emif_instance->pm_functions,
				   sizeof(emif_instance->pm_functions));
	if (!copy_addr)
		return -ENODEV;

	return 0;
}