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
struct intel_vgpu {int /*<<< orphan*/  pv_notified; int /*<<< orphan*/  gvt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_MASK (int) ; 
 int GFX_PPGTT_ENABLE ; 
 int GFX_RUN_LIST_ENABLE ; 
 int /*<<< orphan*/  GVT_FAILSAFE_UNSUPPORTED_GUEST ; 
 int /*<<< orphan*/  INTEL_VGPU_EXECLIST_SUBMISSION ; 
 int _MASKED_BIT_DISABLE (int) ; 
 int _MASKED_BIT_ENABLE (int) ; 
 int /*<<< orphan*/  enter_failsafe_mode (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,char*,int) ; 
 int intel_gvt_render_mmio_to_ring_id (int /*<<< orphan*/ ,unsigned int) ; 
 int intel_vgpu_select_submission_ops (struct intel_vgpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_vgpu_start_schedule (struct intel_vgpu*) ; 
 int /*<<< orphan*/  write_vreg (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int ring_mode_mmio_write(struct intel_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	u32 data = *(u32 *)p_data;
	int ring_id = intel_gvt_render_mmio_to_ring_id(vgpu->gvt, offset);
	bool enable_execlist;
	int ret;

	write_vreg(vgpu, offset, p_data, bytes);

	/* when PPGTT mode enabled, we will check if guest has called
	 * pvinfo, if not, we will treat this guest as non-gvtg-aware
	 * guest, and stop emulating its cfg space, mmio, gtt, etc.
	 */
	if (((data & _MASKED_BIT_ENABLE(GFX_PPGTT_ENABLE)) ||
			(data & _MASKED_BIT_ENABLE(GFX_RUN_LIST_ENABLE)))
			&& !vgpu->pv_notified) {
		enter_failsafe_mode(vgpu, GVT_FAILSAFE_UNSUPPORTED_GUEST);
		return 0;
	}
	if ((data & _MASKED_BIT_ENABLE(GFX_RUN_LIST_ENABLE))
			|| (data & _MASKED_BIT_DISABLE(GFX_RUN_LIST_ENABLE))) {
		enable_execlist = !!(data & GFX_RUN_LIST_ENABLE);

		gvt_dbg_core("EXECLIST %s on ring %d\n",
				(enable_execlist ? "enabling" : "disabling"),
				ring_id);

		if (!enable_execlist)
			return 0;

		ret = intel_vgpu_select_submission_ops(vgpu,
			       ENGINE_MASK(ring_id),
			       INTEL_VGPU_EXECLIST_SUBMISSION);
		if (ret)
			return ret;

		intel_vgpu_start_schedule(vgpu);
	}
	return 0;
}