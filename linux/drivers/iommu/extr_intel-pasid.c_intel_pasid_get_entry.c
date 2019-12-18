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
typedef  int u64 ;
struct pasid_table {struct pasid_dir_entry* table; } ;
struct pasid_entry {int dummy; } ;
struct pasid_dir_entry {int /*<<< orphan*/  val; } ;
struct device_domain_info {TYPE_2__* iommu; } ;
struct TYPE_3__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int PASID_PDE_SHIFT ; 
 int PASID_PTE_MASK ; 
 int PASID_PTE_PRESENT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 struct pasid_entry* alloc_pgtable_page (int /*<<< orphan*/ ) ; 
 struct pasid_entry* get_pasid_table_from_pde (struct pasid_dir_entry*) ; 
 int intel_pasid_get_dev_max_id (struct device*) ; 
 struct pasid_table* intel_pasid_get_table (struct device*) ; 
 int /*<<< orphan*/  pasid_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ virt_to_phys (struct pasid_entry*) ; 

struct pasid_entry *intel_pasid_get_entry(struct device *dev, int pasid)
{
	struct device_domain_info *info;
	struct pasid_table *pasid_table;
	struct pasid_dir_entry *dir;
	struct pasid_entry *entries;
	int dir_index, index;

	pasid_table = intel_pasid_get_table(dev);
	if (WARN_ON(!pasid_table || pasid < 0 ||
		    pasid >= intel_pasid_get_dev_max_id(dev)))
		return NULL;

	dir = pasid_table->table;
	info = dev->archdata.iommu;
	dir_index = pasid >> PASID_PDE_SHIFT;
	index = pasid & PASID_PTE_MASK;

	spin_lock(&pasid_lock);
	entries = get_pasid_table_from_pde(&dir[dir_index]);
	if (!entries) {
		entries = alloc_pgtable_page(info->iommu->node);
		if (!entries) {
			spin_unlock(&pasid_lock);
			return NULL;
		}

		WRITE_ONCE(dir[dir_index].val,
			   (u64)virt_to_phys(entries) | PASID_PTE_PRESENT);
	}
	spin_unlock(&pasid_lock);

	return &entries[index];
}