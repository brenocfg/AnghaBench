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
typedef  int /*<<< orphan*/ * sysmmu_pte_t ;
typedef  int /*<<< orphan*/  sysmmu_iova_t ;
struct sysmmu_fault_info {int /*<<< orphan*/  name; } ;
struct sysmmu_drvdata {int /*<<< orphan*/  sysmmu; int /*<<< orphan*/  pgtable; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ lv1ent_page (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** page_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** section_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_fault_information(struct sysmmu_drvdata *data,
				   const struct sysmmu_fault_info *finfo,
				   sysmmu_iova_t fault_addr)
{
	sysmmu_pte_t *ent;

	dev_err(data->sysmmu, "%s: %s FAULT occurred at %#x\n",
		dev_name(data->master), finfo->name, fault_addr);
	dev_dbg(data->sysmmu, "Page table base: %pa\n", &data->pgtable);
	ent = section_entry(phys_to_virt(data->pgtable), fault_addr);
	dev_dbg(data->sysmmu, "\tLv1 entry: %#x\n", *ent);
	if (lv1ent_page(ent)) {
		ent = page_entry(ent, fault_addr);
		dev_dbg(data->sysmmu, "\t Lv2 entry: %#x\n", *ent);
	}
}