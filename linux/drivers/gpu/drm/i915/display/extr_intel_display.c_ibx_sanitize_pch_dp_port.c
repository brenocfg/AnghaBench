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
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DP_PIPE_SEL (int /*<<< orphan*/ ) ; 
 int DP_PIPE_SEL_MASK ; 
 int DP_PORT_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  port_name (int) ; 

__attribute__((used)) static void ibx_sanitize_pch_dp_port(struct drm_i915_private *dev_priv,
				     enum port port, i915_reg_t dp_reg)
{
	u32 val = I915_READ(dp_reg);

	if (val & DP_PORT_EN ||
	    (val & DP_PIPE_SEL_MASK) == DP_PIPE_SEL(PIPE_A))
		return;

	DRM_DEBUG_KMS("Sanitizing transcoder select for DP %c\n",
		      port_name(port));

	val &= ~DP_PIPE_SEL_MASK;
	val |= DP_PIPE_SEL(PIPE_A);

	I915_WRITE(dp_reg, val);
}