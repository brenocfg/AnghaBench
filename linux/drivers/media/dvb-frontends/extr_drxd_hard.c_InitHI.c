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
struct drxd_state {int /*<<< orphan*/  hi_cfg_ctrl; int /*<<< orphan*/  chip_adr; int /*<<< orphan*/  hi_cfg_wakeup_key; } ;

/* Variables and functions */
 int HI_CfgCommand (struct drxd_state*) ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_CFG_ACT_SLV0_ON ; 

__attribute__((used)) static int InitHI(struct drxd_state *state)
{
	state->hi_cfg_wakeup_key = (state->chip_adr);
	/* port/bridge/power down ctrl */
	state->hi_cfg_ctrl = HI_RA_RAM_SRV_CFG_ACT_SLV0_ON;
	return HI_CfgCommand(state);
}