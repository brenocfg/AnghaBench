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
struct drm_i915_private {int* dpio_phy_iosf_port; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DPIO_DEVFN ; 
 size_t DPIO_PHY (int) ; 
 int /*<<< orphan*/  SB_MWR_NP ; 
 int /*<<< orphan*/  vlv_sideband_rw (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void vlv_dpio_write(struct drm_i915_private *i915,
		    enum pipe pipe, int reg, u32 val)
{
	int port = i915->dpio_phy_iosf_port[DPIO_PHY(pipe)];

	vlv_sideband_rw(i915, DPIO_DEVFN, port, SB_MWR_NP, reg, &val);
}