#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_9__ {TYPE_3__ indirect_ctx; } ;
struct intel_vgpu_workload {int shadow; size_t ring_id; TYPE_4__ wa_ctx; struct intel_vgpu* vgpu; } ;
struct intel_vgpu_submission {int /*<<< orphan*/ * shadow; int /*<<< orphan*/  shadow_ctx_desc_updated; } ;
struct intel_vgpu {TYPE_1__* gvt; struct intel_vgpu_submission submission; } ;
struct TYPE_7__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_6__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 size_t RCS0 ; 
 int intel_gvt_scan_and_shadow_ringbuffer (struct intel_vgpu_workload*) ; 
 int intel_gvt_scan_and_shadow_wa_ctx (TYPE_4__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_shadow_wa_ctx (TYPE_4__*) ; 
 int /*<<< orphan*/  shadow_context_descriptor_update (int /*<<< orphan*/ ,struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  test_and_set_bit (size_t,int /*<<< orphan*/ ) ; 

int intel_gvt_scan_and_shadow_workload(struct intel_vgpu_workload *workload)
{
	struct intel_vgpu *vgpu = workload->vgpu;
	struct intel_vgpu_submission *s = &vgpu->submission;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	int ret;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);

	if (workload->shadow)
		return 0;

	if (!test_and_set_bit(workload->ring_id, s->shadow_ctx_desc_updated))
		shadow_context_descriptor_update(s->shadow[workload->ring_id],
						 workload);

	ret = intel_gvt_scan_and_shadow_ringbuffer(workload);
	if (ret)
		return ret;

	if (workload->ring_id == RCS0 && workload->wa_ctx.indirect_ctx.size) {
		ret = intel_gvt_scan_and_shadow_wa_ctx(&workload->wa_ctx);
		if (ret)
			goto err_shadow;
	}

	workload->shadow = true;
	return 0;
err_shadow:
	release_shadow_wa_ctx(&workload->wa_ctx);
	return ret;
}