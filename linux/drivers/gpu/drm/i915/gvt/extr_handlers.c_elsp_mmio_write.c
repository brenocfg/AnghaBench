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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int index; int /*<<< orphan*/ * data; } ;
struct intel_vgpu_execlist {TYPE_2__ elsp_dwords; } ;
struct TYPE_3__ {struct intel_vgpu_execlist* execlist; } ;
struct intel_vgpu {TYPE_1__ submission; int /*<<< orphan*/  gvt; } ;

/* Variables and functions */
 int EINVAL ; 
 int I915_NUM_ENGINES ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int) ; 
 int intel_gvt_render_mmio_to_ring_id (int /*<<< orphan*/ ,unsigned int) ; 
 int intel_vgpu_submit_execlist (struct intel_vgpu*,int) ; 

__attribute__((used)) static int elsp_mmio_write(struct intel_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	int ring_id = intel_gvt_render_mmio_to_ring_id(vgpu->gvt, offset);
	struct intel_vgpu_execlist *execlist;
	u32 data = *(u32 *)p_data;
	int ret = 0;

	if (WARN_ON(ring_id < 0 || ring_id >= I915_NUM_ENGINES))
		return -EINVAL;

	execlist = &vgpu->submission.execlist[ring_id];

	execlist->elsp_dwords.data[3 - execlist->elsp_dwords.index] = data;
	if (execlist->elsp_dwords.index == 3) {
		ret = intel_vgpu_submit_execlist(vgpu, ring_id);
		if(ret)
			gvt_vgpu_err("fail submit workload on ring %d\n",
				ring_id);
	}

	++execlist->elsp_dwords.index;
	execlist->elsp_dwords.index &= 0x3;
	return ret;
}