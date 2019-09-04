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
struct seq_file {int dummy; } ;
struct omap_iommu {int nr_tlb_entries; } ;
struct cr_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __dump_tlb_entries (struct omap_iommu*,struct cr_regs*,int) ; 
 int /*<<< orphan*/  iotlb_dump_cr (struct omap_iommu*,struct cr_regs*,struct seq_file*) ; 
 struct cr_regs* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cr_regs*) ; 

__attribute__((used)) static size_t omap_dump_tlb_entries(struct omap_iommu *obj, struct seq_file *s)
{
	int i, num;
	struct cr_regs *cr;

	num = obj->nr_tlb_entries;

	cr = kcalloc(num, sizeof(*cr), GFP_KERNEL);
	if (!cr)
		return 0;

	num = __dump_tlb_entries(obj, cr, num);
	for (i = 0; i < num; i++)
		iotlb_dump_cr(obj, cr + i, s);
	kfree(cr);

	return 0;
}