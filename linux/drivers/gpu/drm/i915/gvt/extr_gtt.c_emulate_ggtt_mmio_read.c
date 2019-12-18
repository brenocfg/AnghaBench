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
struct intel_vgpu_mm {int dummy; } ;
struct TYPE_4__ {struct intel_vgpu_mm* ggtt_mm; } ;
struct intel_vgpu {TYPE_1__* gvt; TYPE_2__ gtt; } ;
struct intel_gvt_gtt_entry {int /*<<< orphan*/  val64; } ;
struct intel_gvt_device_info {unsigned int gtt_entry_size_shift; int gtt_entry_size; } ;
struct TYPE_3__ {struct intel_gvt_device_info device_info; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long I915_GTT_PAGE_SHIFT ; 
 int /*<<< orphan*/  ggtt_get_guest_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  gvt_dbg_mm (char*,unsigned long) ; 
 int /*<<< orphan*/  intel_gvt_ggtt_validate_range (struct intel_vgpu*,unsigned long,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int emulate_ggtt_mmio_read(struct intel_vgpu *vgpu,
	unsigned int off, void *p_data, unsigned int bytes)
{
	struct intel_vgpu_mm *ggtt_mm = vgpu->gtt.ggtt_mm;
	const struct intel_gvt_device_info *info = &vgpu->gvt->device_info;
	unsigned long index = off >> info->gtt_entry_size_shift;
	unsigned long gma;
	struct intel_gvt_gtt_entry e;

	if (bytes != 4 && bytes != 8)
		return -EINVAL;

	gma = index << I915_GTT_PAGE_SHIFT;
	if (!intel_gvt_ggtt_validate_range(vgpu,
					   gma, 1 << I915_GTT_PAGE_SHIFT)) {
		gvt_dbg_mm("read invalid ggtt at 0x%lx\n", gma);
		memset(p_data, 0, bytes);
		return 0;
	}

	ggtt_get_guest_entry(ggtt_mm, &e, index);
	memcpy(p_data, (void *)&e.val64 + (off & (info->gtt_entry_size - 1)),
			bytes);
	return 0;
}