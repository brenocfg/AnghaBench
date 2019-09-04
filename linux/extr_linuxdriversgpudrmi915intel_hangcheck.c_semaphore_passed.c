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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ deadlock; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ I915_NUM_ENGINES ; 
 int I915_READ_CTL (struct intel_engine_cs*) ; 
 scalar_t__ IS_ERR (struct intel_engine_cs*) ; 
 int RING_WAIT_SEMAPHORE ; 
 scalar_t__ i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 struct intel_engine_cs* semaphore_waits_for (struct intel_engine_cs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int semaphore_passed(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	struct intel_engine_cs *signaller;
	u32 seqno;

	engine->hangcheck.deadlock++;

	signaller = semaphore_waits_for(engine, &seqno);
	if (signaller == NULL)
		return -1;

	if (IS_ERR(signaller))
		return 0;

	/* Prevent pathological recursion due to driver bugs */
	if (signaller->hangcheck.deadlock >= I915_NUM_ENGINES)
		return -1;

	if (i915_seqno_passed(intel_engine_get_seqno(signaller), seqno))
		return 1;

	/* cursory check for an unkickable deadlock */
	if (I915_READ_CTL(signaller) & RING_WAIT_SEMAPHORE &&
	    semaphore_passed(signaller) < 0)
		return -1;

	return 0;
}