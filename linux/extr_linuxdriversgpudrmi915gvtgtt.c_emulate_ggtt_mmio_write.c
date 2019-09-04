#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long last_partial_off; scalar_t__ last_partial_data; } ;
struct intel_vgpu_mm {TYPE_2__ ggtt_mm; } ;
struct TYPE_4__ {struct intel_vgpu_mm* ggtt_mm; } ;
struct intel_vgpu {TYPE_1__ gtt; struct intel_gvt* gvt; } ;
struct intel_gvt_gtt_pte_ops {unsigned long (* get_pfn ) (struct intel_gvt_gtt_entry*) ;int /*<<< orphan*/  (* clear_present ) (struct intel_gvt_gtt_entry*) ;int /*<<< orphan*/  (* set_pfn ) (struct intel_gvt_gtt_entry*,int) ;scalar_t__ (* test_present ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {scalar_t__ val64; } ;
struct intel_gvt_device_info {unsigned int gtt_entry_size_shift; int gtt_entry_size; } ;
struct TYPE_6__ {int scratch_mfn; struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct intel_gvt {int /*<<< orphan*/  dev_priv; TYPE_3__ gtt; struct intel_gvt_device_info device_info; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long I915_GTT_PAGE_SHIFT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ggtt_get_guest_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  ggtt_get_host_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  ggtt_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggtt_invalidate_pte (struct intel_vgpu*,struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  ggtt_set_guest_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  ggtt_set_host_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,...) ; 
 int intel_gvt_hypervisor_dma_map_guest_page (struct intel_vgpu*,unsigned long,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  intel_gvt_hypervisor_is_valid_gfn (struct intel_vgpu*,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  stub10 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  stub2 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  stub3 (struct intel_gvt_gtt_entry*) ; 
 scalar_t__ stub4 (struct intel_gvt_gtt_entry*) ; 
 unsigned long stub5 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  stub6 (struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  stub7 (struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  stub8 (struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  stub9 (struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  vgpu_gmadr_is_valid (struct intel_vgpu*,unsigned long) ; 

__attribute__((used)) static int emulate_ggtt_mmio_write(struct intel_vgpu *vgpu, unsigned int off,
	void *p_data, unsigned int bytes)
{
	struct intel_gvt *gvt = vgpu->gvt;
	const struct intel_gvt_device_info *info = &gvt->device_info;
	struct intel_vgpu_mm *ggtt_mm = vgpu->gtt.ggtt_mm;
	struct intel_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	unsigned long g_gtt_index = off >> info->gtt_entry_size_shift;
	unsigned long gma, gfn;
	struct intel_gvt_gtt_entry e, m;
	dma_addr_t dma_addr;
	int ret;

	if (bytes != 4 && bytes != 8)
		return -EINVAL;

	gma = g_gtt_index << I915_GTT_PAGE_SHIFT;

	/* the VM may configure the whole GM space when ballooning is used */
	if (!vgpu_gmadr_is_valid(vgpu, gma))
		return 0;

	ggtt_get_guest_entry(ggtt_mm, &e, g_gtt_index);

	memcpy((void *)&e.val64 + (off & (info->gtt_entry_size - 1)), p_data,
			bytes);

	/* If ggtt entry size is 8 bytes, and it's split into two 4 bytes
	 * write, we assume the two 4 bytes writes are consecutive.
	 * Otherwise, we abort and report error
	 */
	if (bytes < info->gtt_entry_size) {
		if (ggtt_mm->ggtt_mm.last_partial_off == -1UL) {
			/* the first partial part*/
			ggtt_mm->ggtt_mm.last_partial_off = off;
			ggtt_mm->ggtt_mm.last_partial_data = e.val64;
			return 0;
		} else if ((g_gtt_index ==
				(ggtt_mm->ggtt_mm.last_partial_off >>
				info->gtt_entry_size_shift)) &&
			(off !=	ggtt_mm->ggtt_mm.last_partial_off)) {
			/* the second partial part */

			int last_off = ggtt_mm->ggtt_mm.last_partial_off &
				(info->gtt_entry_size - 1);

			memcpy((void *)&e.val64 + last_off,
				(void *)&ggtt_mm->ggtt_mm.last_partial_data +
				last_off, bytes);

			ggtt_mm->ggtt_mm.last_partial_off = -1UL;
		} else {
			int last_offset;

			gvt_vgpu_err("failed to populate guest ggtt entry: abnormal ggtt entry write sequence, last_partial_off=%lx, offset=%x, bytes=%d, ggtt entry size=%d\n",
					ggtt_mm->ggtt_mm.last_partial_off, off,
					bytes, info->gtt_entry_size);

			/* set host ggtt entry to scratch page and clear
			 * virtual ggtt entry as not present for last
			 * partially write offset
			 */
			last_offset = ggtt_mm->ggtt_mm.last_partial_off &
					(~(info->gtt_entry_size - 1));

			ggtt_get_host_entry(ggtt_mm, &m, last_offset);
			ggtt_invalidate_pte(vgpu, &m);
			ops->set_pfn(&m, gvt->gtt.scratch_mfn);
			ops->clear_present(&m);
			ggtt_set_host_entry(ggtt_mm, &m, last_offset);
			ggtt_invalidate(gvt->dev_priv);

			ggtt_get_guest_entry(ggtt_mm, &e, last_offset);
			ops->clear_present(&e);
			ggtt_set_guest_entry(ggtt_mm, &e, last_offset);

			ggtt_mm->ggtt_mm.last_partial_off = off;
			ggtt_mm->ggtt_mm.last_partial_data = e.val64;

			return 0;
		}
	}

	if (ops->test_present(&e)) {
		gfn = ops->get_pfn(&e);
		m = e;

		/* one PTE update may be issued in multiple writes and the
		 * first write may not construct a valid gfn
		 */
		if (!intel_gvt_hypervisor_is_valid_gfn(vgpu, gfn)) {
			ops->set_pfn(&m, gvt->gtt.scratch_mfn);
			goto out;
		}

		ret = intel_gvt_hypervisor_dma_map_guest_page(vgpu, gfn,
							PAGE_SIZE, &dma_addr);
		if (ret) {
			gvt_vgpu_err("fail to populate guest ggtt entry\n");
			/* guest driver may read/write the entry when partial
			 * update the entry in this situation p2m will fail
			 * settting the shadow entry to point to a scratch page
			 */
			ops->set_pfn(&m, gvt->gtt.scratch_mfn);
		} else
			ops->set_pfn(&m, dma_addr >> PAGE_SHIFT);
	} else {
		ggtt_get_host_entry(ggtt_mm, &m, g_gtt_index);
		ggtt_invalidate_pte(vgpu, &m);
		ops->set_pfn(&m, gvt->gtt.scratch_mfn);
		ops->clear_present(&m);
	}

out:
	ggtt_set_host_entry(ggtt_mm, &m, g_gtt_index);
	ggtt_invalidate(gvt->dev_priv);
	ggtt_set_guest_entry(ggtt_mm, &e, g_gtt_index);
	return 0;
}