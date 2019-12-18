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
struct i915_perf_stream {struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int GEN10_GT_NOA_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPM_CONFIG1 ; 
 int /*<<< orphan*/  gen8_configure_all_contexts (struct i915_perf_stream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen10_disable_metric_set(struct i915_perf_stream *stream)
{
	struct drm_i915_private *dev_priv = stream->dev_priv;

	/* Reset all contexts' slices/subslices configurations. */
	gen8_configure_all_contexts(stream, NULL);

	/* Make sure we disable noa to save power. */
	I915_WRITE(RPM_CONFIG1,
		   I915_READ(RPM_CONFIG1) & ~GEN10_GT_NOA_ENABLE);
}