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

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_IOSF_SB_PUNIT ; 
 int /*<<< orphan*/  vlv_iosf_sb_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vlv_punit_put(struct drm_i915_private *i915)
{
	vlv_iosf_sb_put(i915, BIT(VLV_IOSF_SB_PUNIT));
}