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
 int /*<<< orphan*/  CNL_REVID_A0 ; 
 scalar_t__ IS_CNL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen9_check_dword_gap (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen9_check_huc_fw_fits (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool check_hw_restrictions(struct drm_i915_private *i915,
					 u32 guc_wopcm_base, u32 guc_wopcm_size,
					 u32 huc_fw_size)
{
	if (IS_GEN(i915, 9) && !gen9_check_dword_gap(i915, guc_wopcm_base,
						     guc_wopcm_size))
		return false;

	if ((IS_GEN(i915, 9) ||
	     IS_CNL_REVID(i915, CNL_REVID_A0, CNL_REVID_A0)) &&
	    !gen9_check_huc_fw_fits(i915, guc_wopcm_size, huc_fw_size))
		return false;

	return true;
}