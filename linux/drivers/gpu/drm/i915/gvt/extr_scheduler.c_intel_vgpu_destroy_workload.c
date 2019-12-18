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
struct intel_vgpu_workload {scalar_t__ shadow_mm; int /*<<< orphan*/  wa_ctx; TYPE_1__* vgpu; } ;
struct intel_vgpu_submission {int /*<<< orphan*/  workloads; } ;
struct TYPE_2__ {struct intel_vgpu_submission submission; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_vgpu_mm_put (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  release_shadow_batch_buffer (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  release_shadow_wa_ctx (int /*<<< orphan*/ *) ; 

void intel_vgpu_destroy_workload(struct intel_vgpu_workload *workload)
{
	struct intel_vgpu_submission *s = &workload->vgpu->submission;

	release_shadow_batch_buffer(workload);
	release_shadow_wa_ctx(&workload->wa_ctx);

	if (workload->shadow_mm)
		intel_vgpu_mm_put(workload->shadow_mm);

	kmem_cache_free(s->workloads, workload);
}