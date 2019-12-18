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
struct intel_uncore {int dummy; } ;
struct i915_perf_stream {TYPE_1__* dev_priv; } ;
struct TYPE_2__ {struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GEN8_OACONTROL ; 
 int /*<<< orphan*/  GEN8_OA_COUNTER_ENABLE ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_wait_for_register (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gen8_oa_disable(struct i915_perf_stream *stream)
{
	struct intel_uncore *uncore = &stream->dev_priv->uncore;

	intel_uncore_write(uncore, GEN8_OACONTROL, 0);
	if (intel_wait_for_register(uncore,
				    GEN8_OACONTROL, GEN8_OA_COUNTER_ENABLE, 0,
				    50))
		DRM_ERROR("wait for OA to be disabled timed out\n");
}