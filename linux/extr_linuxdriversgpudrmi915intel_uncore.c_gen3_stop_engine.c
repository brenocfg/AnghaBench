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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_CTL (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/  const) ; 
 scalar_t__ intel_engine_stop_cs (struct intel_engine_cs*) ; 

__attribute__((used)) static void gen3_stop_engine(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	const u32 base = engine->mmio_base;

	if (intel_engine_stop_cs(engine))
		DRM_DEBUG_DRIVER("%s: timed out on STOP_RING\n", engine->name);

	I915_WRITE_FW(RING_HEAD(base), I915_READ_FW(RING_TAIL(base)));
	POSTING_READ_FW(RING_HEAD(base)); /* paranoia */

	I915_WRITE_FW(RING_HEAD(base), 0);
	I915_WRITE_FW(RING_TAIL(base), 0);
	POSTING_READ_FW(RING_TAIL(base));

	/* The ring must be empty before it is disabled */
	I915_WRITE_FW(RING_CTL(base), 0);

	/* Check acts as a post */
	if (I915_READ_FW(RING_HEAD(base)) != 0)
		DRM_DEBUG_DRIVER("%s: ring head not parked\n",
				 engine->name);
}