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
struct drxd_state {int /*<<< orphan*/  hi_cfg_ctrl; } ;

/* Variables and functions */
 int HI_CfgCommand (struct drxd_state*) ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_CFG_ACT_BRD_OFF ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_CFG_ACT_BRD_ON ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_CFG_ACT_BRD__M ; 

__attribute__((used)) static int DRX_ConfigureI2CBridge(struct drxd_state *state, int bEnableBridge)
{
	state->hi_cfg_ctrl &= (~HI_RA_RAM_SRV_CFG_ACT_BRD__M);
	if (bEnableBridge)
		state->hi_cfg_ctrl |= HI_RA_RAM_SRV_CFG_ACT_BRD_ON;
	else
		state->hi_cfg_ctrl |= HI_RA_RAM_SRV_CFG_ACT_BRD_OFF;

	return HI_CfgCommand(state);
}