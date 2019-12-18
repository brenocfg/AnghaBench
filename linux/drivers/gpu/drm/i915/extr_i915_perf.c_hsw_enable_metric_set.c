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
 int GEN6_CSUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN6_UCGCTL1 ; 
 int GEN7_DOP_CLOCK_GATE_ENABLE ; 
 int /*<<< orphan*/  GEN7_MISCCPCTL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_oa_regs (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay_after_mux () ; 

__attribute__((used)) static int hsw_enable_metric_set(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;
	const struct i915_oa_config *oa_config = stream->oa_config;

	/*
	 * PRM:
	 *
	 * OA unit is using “crclk” for its functionality. When trunk
	 * level clock gating takes place, OA clock would be gated,
	 * unable to count the events from non-render clock domain.
	 * Render clock gating must be disabled when OA is enabled to
	 * count the events from non-render domain. Unit level clock
	 * gating for RCS should also be disabled.
	 */
	I915_WRITE(GEN7_MISCCPCTL, (I915_READ(GEN7_MISCCPCTL) &
				    ~GEN7_DOP_CLOCK_GATE_ENABLE));
	I915_WRITE(GEN6_UCGCTL1, (I915_READ(GEN6_UCGCTL1) |
				  GEN6_CSUNIT_CLOCK_GATE_DISABLE));

	config_oa_regs(dev_priv, oa_config->mux_regs, oa_config->mux_regs_len);
	delay_after_mux();

	config_oa_regs(dev_priv, oa_config->b_counter_regs,
		       oa_config->b_counter_regs_len);

	return 0;
}