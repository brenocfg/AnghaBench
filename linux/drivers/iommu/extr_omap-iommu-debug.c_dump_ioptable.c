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
typedef  int u32 ;
struct seq_file {struct omap_iommu* private; } ;
struct omap_iommu {int /*<<< orphan*/  page_table_lock; } ;

/* Variables and functions */
 int IOPGD_SHIFT ; 
 int IOPGD_TABLE ; 
 int IOPTE_SHIFT ; 
 int PTRS_PER_IOPGD ; 
 int PTRS_PER_IOPTE ; 
 int* iopgd_offset (struct omap_iommu*,int /*<<< orphan*/ ) ; 
 int* iopte_offset (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dump_ioptable(struct seq_file *s)
{
	int i, j;
	u32 da;
	u32 *iopgd, *iopte;
	struct omap_iommu *obj = s->private;

	spin_lock(&obj->page_table_lock);

	iopgd = iopgd_offset(obj, 0);
	for (i = 0; i < PTRS_PER_IOPGD; i++, iopgd++) {
		if (!*iopgd)
			continue;

		if (!(*iopgd & IOPGD_TABLE)) {
			da = i << IOPGD_SHIFT;
			seq_printf(s, "1: 0x%08x 0x%08x\n", da, *iopgd);
			continue;
		}

		iopte = iopte_offset(iopgd, 0);
		for (j = 0; j < PTRS_PER_IOPTE; j++, iopte++) {
			if (!*iopte)
				continue;

			da = (i << IOPGD_SHIFT) + (j << IOPTE_SHIFT);
			seq_printf(s, "2: 0x%08x 0x%08x\n", da, *iopte);
		}
	}

	spin_unlock(&obj->page_table_lock);
}