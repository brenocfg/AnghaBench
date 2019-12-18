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
struct intel_vgpu_submission {TYPE_1__* ops; int /*<<< orphan*/  active; } ;
struct intel_vgpu {struct intel_vgpu_submission submission; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct intel_vgpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  intel_vgpu_clean_workloads (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

void intel_vgpu_reset_submission(struct intel_vgpu *vgpu,
				 intel_engine_mask_t engine_mask)
{
	struct intel_vgpu_submission *s = &vgpu->submission;

	if (!s->active)
		return;

	intel_vgpu_clean_workloads(vgpu, engine_mask);
	s->ops->reset(vgpu, engine_mask);
}