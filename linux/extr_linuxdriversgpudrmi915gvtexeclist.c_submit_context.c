#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_vgpu_workload {int emulate_schedule_in; int /*<<< orphan*/  elsp_dwords; int /*<<< orphan*/  complete; int /*<<< orphan*/  prepare; } ;
struct intel_vgpu_submission {TYPE_1__* execlist; } ;
struct intel_vgpu {struct intel_vgpu_submission submission; } ;
struct execlist_ctx_descriptor_format {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  elsp_dwords; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct intel_vgpu_workload*) ; 
 int PTR_ERR (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  complete_execlist_workload ; 
 int /*<<< orphan*/  gvt_dbg_el (char*,struct intel_vgpu_workload*,int) ; 
 struct intel_vgpu_workload* intel_vgpu_create_workload (struct intel_vgpu*,int,struct execlist_ctx_descriptor_format*) ; 
 int /*<<< orphan*/  intel_vgpu_queue_workload (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  prepare_execlist_workload ; 

__attribute__((used)) static int submit_context(struct intel_vgpu *vgpu, int ring_id,
		struct execlist_ctx_descriptor_format *desc,
		bool emulate_schedule_in)
{
	struct intel_vgpu_submission *s = &vgpu->submission;
	struct intel_vgpu_workload *workload = NULL;

	workload = intel_vgpu_create_workload(vgpu, ring_id, desc);
	if (IS_ERR(workload))
		return PTR_ERR(workload);

	workload->prepare = prepare_execlist_workload;
	workload->complete = complete_execlist_workload;
	workload->emulate_schedule_in = emulate_schedule_in;

	if (emulate_schedule_in)
		workload->elsp_dwords = s->execlist[ring_id].elsp_dwords;

	gvt_dbg_el("workload %p emulate schedule_in %d\n", workload,
			emulate_schedule_in);

	intel_vgpu_queue_workload(workload);
	return 0;
}