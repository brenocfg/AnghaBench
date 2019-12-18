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
struct intel_engine_cs {int /*<<< orphan*/  i915; } ;
struct i915_vma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_LLC (int /*<<< orphan*/ ) ; 
 unsigned int PIN_GLOBAL ; 
 unsigned int PIN_HIGH ; 
 unsigned int PIN_MAPPABLE ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pin_ggtt_status_page(struct intel_engine_cs *engine,
				struct i915_vma *vma)
{
	unsigned int flags;

	flags = PIN_GLOBAL;
	if (!HAS_LLC(engine->i915))
		/*
		 * On g33, we cannot place HWS above 256MiB, so
		 * restrict its pinning to the low mappable arena.
		 * Though this restriction is not documented for
		 * gen4, gen5, or byt, they also behave similarly
		 * and hang if the HWS is placed at the top of the
		 * GTT. To generalise, it appears that all !llc
		 * platforms have issues with us placing the HWS
		 * above the mappable region (even though we never
		 * actually map it).
		 */
		flags |= PIN_MAPPABLE;
	else
		flags |= PIN_HIGH;

	return i915_vma_pin(vma, 0, 0, flags);
}