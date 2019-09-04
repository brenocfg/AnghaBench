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
struct intel_engine_cs {int dummy; } ;
struct drm_i915_private {struct intel_engine_cs const** engine; } ;

/* Variables and functions */
 unsigned int I915_NUM_ENGINES ; 

__attribute__((used)) static inline const struct intel_engine_cs *
engine_lookup(const struct drm_i915_private *i915, unsigned int id)
{
	if (id >= I915_NUM_ENGINES)
		return NULL;

	return i915->engine[id];
}