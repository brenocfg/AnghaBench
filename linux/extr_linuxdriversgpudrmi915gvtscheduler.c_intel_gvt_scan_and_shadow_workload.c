#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ size; } ;
struct TYPE_11__ {TYPE_4__ indirect_ctx; } ;
struct TYPE_9__ {int addressing_mode; } ;
struct intel_vgpu_workload {size_t ring_id; TYPE_5__ wa_ctx; int /*<<< orphan*/  req; TYPE_3__ ctx_desc; struct intel_vgpu* vgpu; } ;
struct intel_vgpu_submission {int /*<<< orphan*/  shadow_ctx_desc_updated; struct i915_gem_context* shadow_ctx; } ;
struct intel_vgpu {TYPE_1__* gvt; struct intel_vgpu_submission submission; } ;
struct intel_engine_cs {int dummy; } ;
struct intel_context {int dummy; } ;
typedef  struct intel_context i915_request ;
struct i915_gem_context {int desc_template; } ;
struct TYPE_8__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; struct intel_engine_cs** engine; } ;
struct TYPE_7__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int GEN8_CTX_ADDRESSING_MODE_SHIFT ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int PTR_ERR (struct intel_context*) ; 
 size_t RCS ; 
 struct intel_context* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 struct intel_context* i915_request_alloc (struct intel_engine_cs*,struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_request_get (struct intel_context*) ; 
 int /*<<< orphan*/  i915_request_put (struct intel_context*) ; 
 struct intel_context* intel_context_pin (struct i915_gem_context*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_context_unpin (struct intel_context*) ; 
 int intel_gvt_scan_and_shadow_ringbuffer (struct intel_vgpu_workload*) ; 
 int intel_gvt_scan_and_shadow_wa_ctx (TYPE_5__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int populate_shadow_context (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  release_shadow_wa_ctx (TYPE_5__*) ; 
 int /*<<< orphan*/  shadow_context_descriptor_update (struct intel_context*) ; 
 int /*<<< orphan*/  test_and_set_bit (size_t,int /*<<< orphan*/ ) ; 

int intel_gvt_scan_and_shadow_workload(struct intel_vgpu_workload *workload)
{
	struct intel_vgpu *vgpu = workload->vgpu;
	struct intel_vgpu_submission *s = &vgpu->submission;
	struct i915_gem_context *shadow_ctx = s->shadow_ctx;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	struct intel_engine_cs *engine = dev_priv->engine[workload->ring_id];
	struct intel_context *ce;
	struct i915_request *rq;
	int ret;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);

	if (workload->req)
		return 0;

	/* pin shadow context by gvt even the shadow context will be pinned
	 * when i915 alloc request. That is because gvt will update the guest
	 * context from shadow context when workload is completed, and at that
	 * moment, i915 may already unpined the shadow context to make the
	 * shadow_ctx pages invalid. So gvt need to pin itself. After update
	 * the guest context, gvt can unpin the shadow_ctx safely.
	 */
	ce = intel_context_pin(shadow_ctx, engine);
	if (IS_ERR(ce)) {
		gvt_vgpu_err("fail to pin shadow context\n");
		return PTR_ERR(ce);
	}

	shadow_ctx->desc_template &= ~(0x3 << GEN8_CTX_ADDRESSING_MODE_SHIFT);
	shadow_ctx->desc_template |= workload->ctx_desc.addressing_mode <<
				    GEN8_CTX_ADDRESSING_MODE_SHIFT;

	if (!test_and_set_bit(workload->ring_id, s->shadow_ctx_desc_updated))
		shadow_context_descriptor_update(ce);

	ret = intel_gvt_scan_and_shadow_ringbuffer(workload);
	if (ret)
		goto err_unpin;

	if ((workload->ring_id == RCS) &&
	    (workload->wa_ctx.indirect_ctx.size != 0)) {
		ret = intel_gvt_scan_and_shadow_wa_ctx(&workload->wa_ctx);
		if (ret)
			goto err_shadow;
	}

	rq = i915_request_alloc(engine, shadow_ctx);
	if (IS_ERR(rq)) {
		gvt_vgpu_err("fail to allocate gem request\n");
		ret = PTR_ERR(rq);
		goto err_shadow;
	}
	workload->req = i915_request_get(rq);

	ret = populate_shadow_context(workload);
	if (ret)
		goto err_req;

	return 0;
err_req:
	rq = fetch_and_zero(&workload->req);
	i915_request_put(rq);
err_shadow:
	release_shadow_wa_ctx(&workload->wa_ctx);
err_unpin:
	intel_context_unpin(ce);
	return ret;
}