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
struct i915_perf_stream {struct i915_oa_config* oa_config; struct drm_i915_private* dev_priv; } ;
struct i915_oa_config {int /*<<< orphan*/  b_counter_regs_len; int /*<<< orphan*/  b_counter_regs; int /*<<< orphan*/  mux_regs_len; int /*<<< orphan*/  mux_regs; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_OA_DEBUG ; 
 int GEN9_OA_DEBUG_DISABLE_CLK_RATIO_REPORTS ; 
 int GEN9_OA_DEBUG_INCLUDE_CLK_RATIO ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int) ; 
 int /*<<< orphan*/  config_oa_regs (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay_after_mux () ; 
 int gen8_configure_all_contexts (struct i915_perf_stream*,struct i915_oa_config const*) ; 

__attribute__((used)) static int gen8_enable_metric_set(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;
	const struct i915_oa_config *oa_config = stream->oa_config;
	int ret;

	/*
	 * We disable slice/unslice clock ratio change reports on SKL since
	 * they are too noisy. The HW generates a lot of redundant reports
	 * where the ratio hasn't really changed causing a lot of redundant
	 * work to processes and increasing the chances we'll hit buffer
	 * overruns.
	 *
	 * Although we don't currently use the 'disable overrun' OABUFFER
	 * feature it's worth noting that clock ratio reports have to be
	 * disabled before considering to use that feature since the HW doesn't
	 * correctly block these reports.
	 *
	 * Currently none of the high-level metrics we have depend on knowing
	 * this ratio to normalize.
	 *
	 * Note: This register is not power context saved and restored, but
	 * that's OK considering that we disable RC6 while the OA unit is
	 * enabled.
	 *
	 * The _INCLUDE_CLK_RATIO bit allows the slice/unslice frequency to
	 * be read back from automatically triggered reports, as part of the
	 * RPT_ID field.
	 */
	if (IS_GEN_RANGE(dev_priv, 9, 11)) {
		I915_WRITE(GEN8_OA_DEBUG,
			   _MASKED_BIT_ENABLE(GEN9_OA_DEBUG_DISABLE_CLK_RATIO_REPORTS |
					      GEN9_OA_DEBUG_INCLUDE_CLK_RATIO));
	}

	/*
	 * Update all contexts prior writing the mux configurations as we need
	 * to make sure all slices/subslices are ON before writing to NOA
	 * registers.
	 */
	ret = gen8_configure_all_contexts(stream, oa_config);
	if (ret)
		return ret;

	config_oa_regs(dev_priv, oa_config->mux_regs, oa_config->mux_regs_len);
	delay_after_mux();

	config_oa_regs(dev_priv, oa_config->b_counter_regs,
		       oa_config->b_counter_regs_len);

	return 0;
}