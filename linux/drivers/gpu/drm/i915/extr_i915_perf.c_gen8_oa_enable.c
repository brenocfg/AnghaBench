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
typedef  int u32 ;
struct TYPE_2__ {int format; } ;
struct i915_perf_stream {TYPE_1__ oa_buffer; struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_OACONTROL ; 
 int GEN8_OA_COUNTER_ENABLE ; 
 int GEN8_OA_REPORT_FORMAT_SHIFT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen8_init_oa_buffer (struct i915_perf_stream*) ; 

__attribute__((used)) static void gen8_oa_enable(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;
	u32 report_format = stream->oa_buffer.format;

	/*
	 * Reset buf pointers so we don't forward reports from before now.
	 *
	 * Think carefully if considering trying to avoid this, since it
	 * also ensures status flags and the buffer itself are cleared
	 * in error paths, and we have checks for invalid reports based
	 * on the assumption that certain fields are written to zeroed
	 * memory which this helps maintains.
	 */
	gen8_init_oa_buffer(stream);

	/*
	 * Note: we don't rely on the hardware to perform single context
	 * filtering and instead filter on the cpu based on the context-id
	 * field of reports
	 */
	I915_WRITE(GEN8_OACONTROL, (report_format <<
				    GEN8_OA_REPORT_FORMAT_SHIFT) |
				   GEN8_OA_COUNTER_ENABLE);
}