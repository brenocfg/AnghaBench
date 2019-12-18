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
struct drm_i915_private {int* dpio_phy_iosf_port; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DPIO_DEVFN ; 
 size_t DPIO_PHY (int) ; 
 int /*<<< orphan*/  SB_MRD_NP ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  vlv_sideband_rw (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*) ; 

u32 vlv_dpio_read(struct drm_i915_private *i915, enum pipe pipe, int reg)
{
	int port = i915->dpio_phy_iosf_port[DPIO_PHY(pipe)];
	u32 val = 0;

	vlv_sideband_rw(i915, DPIO_DEVFN, port, SB_MRD_NP, reg, &val);

	/*
	 * FIXME: There might be some registers where all 1's is a valid value,
	 * so ideally we should check the register offset instead...
	 */
	WARN(val == 0xffffffff, "DPIO read pipe %c reg 0x%x == 0x%x\n",
	     pipe_name(pipe), reg, val);

	return val;
}