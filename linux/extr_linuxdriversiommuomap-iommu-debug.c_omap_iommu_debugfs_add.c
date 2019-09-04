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
struct omap_iommu {int /*<<< orphan*/  debug_dir; int /*<<< orphan*/  nr_tlb_entries; int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ADD_FILE_RO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_debug_root ; 
 int /*<<< orphan*/  pagetable ; 
 int /*<<< orphan*/  regs ; 
 int /*<<< orphan*/  tlb ; 

void omap_iommu_debugfs_add(struct omap_iommu *obj)
{
	struct dentry *d;

	if (!iommu_debug_root)
		return;

	obj->debug_dir = debugfs_create_dir(obj->name, iommu_debug_root);
	if (!obj->debug_dir)
		return;

	d = debugfs_create_u32("nr_tlb_entries", 0400, obj->debug_dir,
			       &obj->nr_tlb_entries);
	if (!d)
		return;

	DEBUG_ADD_FILE_RO(regs);
	DEBUG_ADD_FILE_RO(tlb);
	DEBUG_ADD_FILE_RO(pagetable);

	return;

err:
	debugfs_remove_recursive(obj->debug_dir);
}