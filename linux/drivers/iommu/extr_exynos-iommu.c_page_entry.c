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
typedef  int /*<<< orphan*/  sysmmu_pte_t ;
typedef  int /*<<< orphan*/  sysmmu_iova_t ;

/* Variables and functions */
 int lv2ent_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv2table_base (int /*<<< orphan*/ *) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sysmmu_pte_t *page_entry(sysmmu_pte_t *sent, sysmmu_iova_t iova)
{
	return (sysmmu_pte_t *)phys_to_virt(
				lv2table_base(sent)) + lv2ent_offset(iova);
}