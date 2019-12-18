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
struct drm_i915_private {int dummy; } ;
typedef  enum i915_map_type { ____Placeholder_i915_map_type } i915_map_type ;

/* Variables and functions */
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 int I915_MAP_WB ; 
 int I915_MAP_WC ; 

__attribute__((used)) static inline enum i915_map_type
i915_coherent_map_type(struct drm_i915_private *i915)
{
	return HAS_LLC(i915) ? I915_MAP_WB : I915_MAP_WC;
}