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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_WOPCM_RC6_CTX_RESERVED ; 
 int /*<<< orphan*/  CNL_WOPCM_HW_CTX_RESERVED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 

__attribute__((used)) static inline u32 context_reserved_size(struct drm_i915_private *i915)
{
	if (IS_GEN9_LP(i915))
		return BXT_WOPCM_RC6_CTX_RESERVED;
	else if (INTEL_GEN(i915) >= 10)
		return CNL_WOPCM_HW_CTX_RESERVED;
	else
		return 0;
}