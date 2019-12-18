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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mask; int /*<<< orphan*/  gt; int /*<<< orphan*/  i915; } ;
typedef  enum intel_engine_hangcheck_action { ____Placeholder_intel_engine_hangcheck_action } intel_engine_hangcheck_action ;

/* Variables and functions */
 int ENGINE_DEAD ; 
 int ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int ENGINE_WAIT_KICK ; 
 int /*<<< orphan*/  ENGINE_WRITE (struct intel_engine_cs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RING_CTL ; 
 int RING_WAIT ; 
 int head_stuck (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gt_handle_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum intel_engine_hangcheck_action
engine_stuck(struct intel_engine_cs *engine, u64 acthd)
{
	enum intel_engine_hangcheck_action ha;
	u32 tmp;

	ha = head_stuck(engine, acthd);
	if (ha != ENGINE_DEAD)
		return ha;

	if (IS_GEN(engine->i915, 2))
		return ENGINE_DEAD;

	/* Is the chip hanging on a WAIT_FOR_EVENT?
	 * If so we can simply poke the RB_WAIT bit
	 * and break the hang. This should work on
	 * all but the second generation chipsets.
	 */
	tmp = ENGINE_READ(engine, RING_CTL);
	if (tmp & RING_WAIT) {
		intel_gt_handle_error(engine->gt, engine->mask, 0,
				      "stuck wait on %s", engine->name);
		ENGINE_WRITE(engine, RING_CTL, tmp);
		return ENGINE_WAIT_KICK;
	}

	return ENGINE_DEAD;
}