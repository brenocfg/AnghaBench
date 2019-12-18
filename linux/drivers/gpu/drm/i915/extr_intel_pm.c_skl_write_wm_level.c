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
typedef  int u32 ;
struct skl_wm_level {int plane_res_b; int plane_res_l; scalar_t__ ignore_lines; scalar_t__ plane_en; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int PLANE_WM_EN ; 
 int PLANE_WM_IGNORE_LINES ; 
 int PLANE_WM_LINES_SHIFT ; 

__attribute__((used)) static void skl_write_wm_level(struct drm_i915_private *dev_priv,
			       i915_reg_t reg,
			       const struct skl_wm_level *level)
{
	u32 val = 0;

	if (level->plane_en)
		val |= PLANE_WM_EN;
	if (level->ignore_lines)
		val |= PLANE_WM_IGNORE_LINES;
	val |= level->plane_res_b;
	val |= level->plane_res_l << PLANE_WM_LINES_SHIFT;

	I915_WRITE_FW(reg, val);
}