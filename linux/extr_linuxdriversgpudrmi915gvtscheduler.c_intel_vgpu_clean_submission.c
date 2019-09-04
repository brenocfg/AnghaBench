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
struct intel_vgpu_submission {int /*<<< orphan*/  workloads; int /*<<< orphan*/  shadow_ctx; } ;
struct intel_vgpu {struct intel_vgpu_submission submission; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int /*<<< orphan*/  i915_gem_context_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_vgpu_select_submission_ops (struct intel_vgpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 

void intel_vgpu_clean_submission(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_submission *s = &vgpu->submission;

	intel_vgpu_select_submission_ops(vgpu, ALL_ENGINES, 0);
	i915_gem_context_put(s->shadow_ctx);
	kmem_cache_destroy(s->workloads);
}