#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i915_gem_context {int dummy; } ;
struct TYPE_5__ {int format; } ;
struct TYPE_7__ {int specific_ctx_id; int periodic; int period_exponent; TYPE_1__ oa_buffer; TYPE_2__* exclusive_stream; } ;
struct TYPE_8__ {TYPE_3__ oa; } ;
struct drm_i915_private {TYPE_4__ perf; } ;
struct TYPE_6__ {struct i915_gem_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_OACONTROL ; 
 int GEN7_OACONTROL_CTX_MASK ; 
 int GEN7_OACONTROL_ENABLE ; 
 int GEN7_OACONTROL_FORMAT_SHIFT ; 
 int GEN7_OACONTROL_PER_CTX_ENABLE ; 
 int GEN7_OACONTROL_TIMER_ENABLE ; 
 int GEN7_OACONTROL_TIMER_PERIOD_SHIFT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen7_init_oa_buffer (struct drm_i915_private*) ; 

__attribute__((used)) static void gen7_oa_enable(struct drm_i915_private *dev_priv)
{
	struct i915_gem_context *ctx =
			dev_priv->perf.oa.exclusive_stream->ctx;
	u32 ctx_id = dev_priv->perf.oa.specific_ctx_id;
	bool periodic = dev_priv->perf.oa.periodic;
	u32 period_exponent = dev_priv->perf.oa.period_exponent;
	u32 report_format = dev_priv->perf.oa.oa_buffer.format;

	/*
	 * Reset buf pointers so we don't forward reports from before now.
	 *
	 * Think carefully if considering trying to avoid this, since it
	 * also ensures status flags and the buffer itself are cleared
	 * in error paths, and we have checks for invalid reports based
	 * on the assumption that certain fields are written to zeroed
	 * memory which this helps maintains.
	 */
	gen7_init_oa_buffer(dev_priv);

	I915_WRITE(GEN7_OACONTROL,
		   (ctx_id & GEN7_OACONTROL_CTX_MASK) |
		   (period_exponent <<
		    GEN7_OACONTROL_TIMER_PERIOD_SHIFT) |
		   (periodic ? GEN7_OACONTROL_TIMER_ENABLE : 0) |
		   (report_format << GEN7_OACONTROL_FORMAT_SHIFT) |
		   (ctx ? GEN7_OACONTROL_PER_CTX_ENABLE : 0) |
		   GEN7_OACONTROL_ENABLE);
}