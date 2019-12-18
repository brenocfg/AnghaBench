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
struct drm_i915_private {int dummy; } ;
struct cnl_procmon {int dw1; int dw9; int dw10; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW1 (int) ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW10 (int) ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW9 (int) ; 
 struct cnl_procmon* cnl_get_procmon_ref_values (struct drm_i915_private*,int) ; 

__attribute__((used)) static void cnl_set_procmon_ref_values(struct drm_i915_private *dev_priv,
				       enum phy phy)
{
	const struct cnl_procmon *procmon;
	u32 val;

	procmon = cnl_get_procmon_ref_values(dev_priv, phy);

	val = I915_READ(ICL_PORT_COMP_DW1(phy));
	val &= ~((0xff << 16) | 0xff);
	val |= procmon->dw1;
	I915_WRITE(ICL_PORT_COMP_DW1(phy), val);

	I915_WRITE(ICL_PORT_COMP_DW9(phy), procmon->dw9);
	I915_WRITE(ICL_PORT_COMP_DW10(phy), procmon->dw10);
}