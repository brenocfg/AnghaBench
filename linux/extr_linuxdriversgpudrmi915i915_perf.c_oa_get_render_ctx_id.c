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
struct intel_context {int /*<<< orphan*/  lrc_desc; int /*<<< orphan*/  state; } ;
struct i915_perf_stream {int /*<<< orphan*/  ctx; struct drm_i915_private* dev_priv; } ;
struct TYPE_3__ {int specific_ctx_id; unsigned int specific_ctx_id_mask; } ;
struct TYPE_4__ {TYPE_1__ oa; } ;
struct drm_i915_private {TYPE_2__ perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  GEN11_ENGINE_CLASS_SHIFT ; 
 int GEN11_ENGINE_CLASS_WIDTH ; 
 int /*<<< orphan*/  GEN11_ENGINE_INSTANCE_SHIFT ; 
 unsigned int GEN11_ENGINE_INSTANCE_WIDTH ; 
 int /*<<< orphan*/  GEN11_SW_CTX_ID_SHIFT ; 
 unsigned int GEN11_SW_CTX_ID_WIDTH ; 
 unsigned int GEN8_CTX_ID_WIDTH ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int PTR_ERR (struct intel_context*) ; 
 int /*<<< orphan*/  USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct intel_context* oa_pin_context (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oa_get_render_ctx_id(struct i915_perf_stream *stream)
{
	struct drm_i915_private *i915 = stream->dev_priv;
	struct intel_context *ce;

	ce = oa_pin_context(i915, stream->ctx);
	if (IS_ERR(ce))
		return PTR_ERR(ce);

	switch (INTEL_GEN(i915)) {
	case 7: {
		/*
		 * On Haswell we don't do any post processing of the reports
		 * and don't need to use the mask.
		 */
		i915->perf.oa.specific_ctx_id = i915_ggtt_offset(ce->state);
		i915->perf.oa.specific_ctx_id_mask = 0;
		break;
	}

	case 8:
	case 9:
	case 10:
		if (USES_GUC_SUBMISSION(i915)) {
			/*
			 * When using GuC, the context descriptor we write in
			 * i915 is read by GuC and rewritten before it's
			 * actually written into the hardware. The LRCA is
			 * what is put into the context id field of the
			 * context descriptor by GuC. Because it's aligned to
			 * a page, the lower 12bits are always at 0 and
			 * dropped by GuC. They won't be part of the context
			 * ID in the OA reports, so squash those lower bits.
			 */
			i915->perf.oa.specific_ctx_id =
				lower_32_bits(ce->lrc_desc) >> 12;

			/*
			 * GuC uses the top bit to signal proxy submission, so
			 * ignore that bit.
			 */
			i915->perf.oa.specific_ctx_id_mask =
				(1U << (GEN8_CTX_ID_WIDTH - 1)) - 1;
		} else {
			i915->perf.oa.specific_ctx_id_mask =
				(1U << GEN8_CTX_ID_WIDTH) - 1;
			i915->perf.oa.specific_ctx_id =
				upper_32_bits(ce->lrc_desc);
			i915->perf.oa.specific_ctx_id &=
				i915->perf.oa.specific_ctx_id_mask;
		}
		break;

	case 11: {
		i915->perf.oa.specific_ctx_id_mask =
			((1U << GEN11_SW_CTX_ID_WIDTH) - 1) << (GEN11_SW_CTX_ID_SHIFT - 32) |
			((1U << GEN11_ENGINE_INSTANCE_WIDTH) - 1) << (GEN11_ENGINE_INSTANCE_SHIFT - 32) |
			((1 << GEN11_ENGINE_CLASS_WIDTH) - 1) << (GEN11_ENGINE_CLASS_SHIFT - 32);
		i915->perf.oa.specific_ctx_id = upper_32_bits(ce->lrc_desc);
		i915->perf.oa.specific_ctx_id &=
			i915->perf.oa.specific_ctx_id_mask;
		break;
	}

	default:
		MISSING_CASE(INTEL_GEN(i915));
	}

	DRM_DEBUG_DRIVER("filtering on ctx_id=0x%x ctx_id_mask=0x%x\n",
			 i915->perf.oa.specific_ctx_id,
			 i915->perf.oa.specific_ctx_id_mask);

	return 0;
}