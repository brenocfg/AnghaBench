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
struct omap_iommu {int /*<<< orphan*/  nr_tlb_entries; struct dentry* debug_dir; int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct omap_iommu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_debug_root ; 
 int /*<<< orphan*/  pagetable_fops ; 
 int /*<<< orphan*/  regs_fops ; 
 int /*<<< orphan*/  tlb_fops ; 

void omap_iommu_debugfs_add(struct omap_iommu *obj)
{
	struct dentry *d;

	if (!iommu_debug_root)
		return;

	d = debugfs_create_dir(obj->name, iommu_debug_root);
	obj->debug_dir = d;

	debugfs_create_u32("nr_tlb_entries", 0400, d, &obj->nr_tlb_entries);
	debugfs_create_file("regs", 0400, d, obj, &regs_fops);
	debugfs_create_file("tlb", 0400, d, obj, &tlb_fops);
	debugfs_create_file("pagetable", 0400, d, obj, &pagetable_fops);
}