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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct seq_file {int dummy; } ;
struct intel_iommu {int /*<<< orphan*/  lock; int /*<<< orphan*/  root_entry; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_tbl_walk (struct seq_file*,struct intel_iommu*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void root_tbl_walk(struct seq_file *m, struct intel_iommu *iommu)
{
	unsigned long flags;
	u16 bus;

	spin_lock_irqsave(&iommu->lock, flags);
	seq_printf(m, "IOMMU %s: Root Table Address: 0x%llx\n", iommu->name,
		   (u64)virt_to_phys(iommu->root_entry));
	seq_puts(m, "B.D.F\tRoot_entry\t\t\t\tContext_entry\t\t\t\tPASID\tPASID_table_entry\n");

	/*
	 * No need to check if the root entry is present or not because
	 * iommu_context_addr() performs the same check before returning
	 * context entry.
	 */
	for (bus = 0; bus < 256; bus++)
		ctx_tbl_walk(m, iommu, bus);

	spin_unlock_irqrestore(&iommu->lock, flags);
}