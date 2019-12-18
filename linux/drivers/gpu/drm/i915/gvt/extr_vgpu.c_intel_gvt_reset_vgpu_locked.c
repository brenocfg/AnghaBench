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
struct intel_vgpu {int failsafe; int pv_notified; int /*<<< orphan*/  id; scalar_t__ resetting_eng; int /*<<< orphan*/  vgpu_lock; struct intel_gvt* gvt; } ;
struct intel_gvt_workload_scheduler {int /*<<< orphan*/ * current_vgpu; } ;
struct intel_gvt {struct intel_gvt_workload_scheduler scheduler; } ;
typedef  scalar_t__ intel_engine_mask_t ;

/* Variables and functions */
 scalar_t__ ALL_ENGINES ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,...) ; 
 int /*<<< orphan*/  intel_gvt_wait_vgpu_idle (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_invalidate_ppgtt (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_reset_cfg_space (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_reset_display (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_reset_gtt (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_reset_mmio (struct intel_vgpu*,int) ; 
 int /*<<< orphan*/  intel_vgpu_reset_resource (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_reset_submission (struct intel_vgpu*,scalar_t__) ; 
 int /*<<< orphan*/  intel_vgpu_select_submission_ops (struct intel_vgpu*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_vgpu_stop_schedule (struct intel_vgpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  populate_pvinfo_page (struct intel_vgpu*) ; 

void intel_gvt_reset_vgpu_locked(struct intel_vgpu *vgpu, bool dmlr,
				 intel_engine_mask_t engine_mask)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct intel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	intel_engine_mask_t resetting_eng = dmlr ? ALL_ENGINES : engine_mask;

	gvt_dbg_core("------------------------------------------\n");
	gvt_dbg_core("resseting vgpu%d, dmlr %d, engine_mask %08x\n",
		     vgpu->id, dmlr, engine_mask);

	vgpu->resetting_eng = resetting_eng;

	intel_vgpu_stop_schedule(vgpu);
	/*
	 * The current_vgpu will set to NULL after stopping the
	 * scheduler when the reset is triggered by current vgpu.
	 */
	if (scheduler->current_vgpu == NULL) {
		mutex_unlock(&vgpu->vgpu_lock);
		intel_gvt_wait_vgpu_idle(vgpu);
		mutex_lock(&vgpu->vgpu_lock);
	}

	intel_vgpu_reset_submission(vgpu, resetting_eng);
	/* full GPU reset or device model level reset */
	if (engine_mask == ALL_ENGINES || dmlr) {
		intel_vgpu_select_submission_ops(vgpu, ALL_ENGINES, 0);
		intel_vgpu_invalidate_ppgtt(vgpu);
		/*fence will not be reset during virtual reset */
		if (dmlr) {
			intel_vgpu_reset_gtt(vgpu);
			intel_vgpu_reset_resource(vgpu);
		}

		intel_vgpu_reset_mmio(vgpu, dmlr);
		populate_pvinfo_page(vgpu);
		intel_vgpu_reset_display(vgpu);

		if (dmlr) {
			intel_vgpu_reset_cfg_space(vgpu);
			/* only reset the failsafe mode when dmlr reset */
			vgpu->failsafe = false;
			vgpu->pv_notified = false;
		}
	}

	vgpu->resetting_eng = 0;
	gvt_dbg_core("reset vgpu%d done\n", vgpu->id);
	gvt_dbg_core("------------------------------------------\n");
}