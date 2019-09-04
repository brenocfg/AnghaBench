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
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DPIO_DEVFN ; 
 int /*<<< orphan*/  DPIO_PHY (int) ; 
 int /*<<< orphan*/  DPIO_PHY_IOSF_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_MWR_NP ; 
 int /*<<< orphan*/  vlv_sideband_rw (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void vlv_dpio_write(struct drm_i915_private *dev_priv, enum pipe pipe, int reg, u32 val)
{
	vlv_sideband_rw(dev_priv, DPIO_DEVFN, DPIO_PHY_IOSF_PORT(DPIO_PHY(pipe)),
			SB_MWR_NP, reg, &val);
}