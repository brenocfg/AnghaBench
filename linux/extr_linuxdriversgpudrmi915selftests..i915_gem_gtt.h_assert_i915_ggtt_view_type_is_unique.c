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
typedef  enum i915_ggtt_view_type { ____Placeholder_i915_ggtt_view_type } i915_ggtt_view_type ;

/* Variables and functions */
#define  I915_GGTT_VIEW_NORMAL 130 
#define  I915_GGTT_VIEW_PARTIAL 129 
#define  I915_GGTT_VIEW_ROTATED 128 

__attribute__((used)) static inline void assert_i915_ggtt_view_type_is_unique(void)
{
	/* As we encode the size of each branch inside the union into its type,
	 * we have to be careful that each branch has a unique size.
	 */
	switch ((enum i915_ggtt_view_type)0) {
	case I915_GGTT_VIEW_NORMAL:
	case I915_GGTT_VIEW_PARTIAL:
	case I915_GGTT_VIEW_ROTATED:
		/* gcc complains if these are identical cases */
		break;
	}
}