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
typedef  int u64 ;
typedef  int u16 ;
struct tbl_walk {int bus; int devfn; struct context_entry* ctx_entry; int /*<<< orphan*/ * rt_entry; int /*<<< orphan*/  member_0; } ;
struct seq_file {struct tbl_walk* private; } ;
struct intel_iommu {scalar_t__ reg; int /*<<< orphan*/ * root_entry; } ;
struct context_entry {int lo; } ;

/* Variables and functions */
 scalar_t__ DMAR_RTADDR_REG ; 
 int DMA_RTADDR_SMT ; 
 int VTD_PAGE_MASK ; 
 int /*<<< orphan*/  context_present (struct context_entry*) ; 
 int dmar_readq (scalar_t__) ; 
 int get_pasid_dir_size (struct context_entry*) ; 
 struct context_entry* iommu_context_addr (struct intel_iommu*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_dir_walk (struct seq_file*,int,int) ; 
 int /*<<< orphan*/  print_tbl_walk (struct seq_file*) ; 

__attribute__((used)) static void ctx_tbl_walk(struct seq_file *m, struct intel_iommu *iommu, u16 bus)
{
	struct context_entry *context;
	u16 devfn, pasid_dir_size;
	u64 pasid_dir_ptr;

	for (devfn = 0; devfn < 256; devfn++) {
		struct tbl_walk tbl_wlk = {0};

		/*
		 * Scalable mode root entry points to upper scalable mode
		 * context table and lower scalable mode context table. Each
		 * scalable mode context table has 128 context entries where as
		 * legacy mode context table has 256 context entries. So in
		 * scalable mode, the context entries for former 128 devices are
		 * in the lower scalable mode context table, while the latter
		 * 128 devices are in the upper scalable mode context table.
		 * In scalable mode, when devfn > 127, iommu_context_addr()
		 * automatically refers to upper scalable mode context table and
		 * hence the caller doesn't have to worry about differences
		 * between scalable mode and non scalable mode.
		 */
		context = iommu_context_addr(iommu, bus, devfn, 0);
		if (!context)
			return;

		if (!context_present(context))
			continue;

		tbl_wlk.bus = bus;
		tbl_wlk.devfn = devfn;
		tbl_wlk.rt_entry = &iommu->root_entry[bus];
		tbl_wlk.ctx_entry = context;
		m->private = &tbl_wlk;

		if (dmar_readq(iommu->reg + DMAR_RTADDR_REG) & DMA_RTADDR_SMT) {
			pasid_dir_ptr = context->lo & VTD_PAGE_MASK;
			pasid_dir_size = get_pasid_dir_size(context);
			pasid_dir_walk(m, pasid_dir_ptr, pasid_dir_size);
			continue;
		}

		print_tbl_walk(m);
	}
}