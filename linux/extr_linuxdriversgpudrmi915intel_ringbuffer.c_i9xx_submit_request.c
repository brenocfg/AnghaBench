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
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  ring; int /*<<< orphan*/  engine; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_TAIL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_submit (struct i915_request*) ; 
 int /*<<< orphan*/  intel_ring_set_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_submit_request(struct i915_request *request)
{
	struct drm_i915_private *dev_priv = request->i915;

	i915_request_submit(request);

	I915_WRITE_TAIL(request->engine,
			intel_ring_set_tail(request->ring, request->tail));
}