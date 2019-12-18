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
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (unsigned short,int /*<<< orphan*/ *) ; 

void cxgb4_clear_msix_aff(unsigned short vec, cpumask_var_t aff_mask)
{
	irq_set_affinity_hint(vec, NULL);
	free_cpumask_var(aff_mask);
}