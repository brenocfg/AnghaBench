#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mxl {TYPE_1__* base; } ;
struct TYPE_2__ {scalar_t__ can_clkout; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYDRA_CRYSTAL_CAP ; 
 int /*<<< orphan*/  HYDRA_CRYSTAL_SETTING ; 
 int /*<<< orphan*/  update_by_mnemonic (struct mxl*,int,int,int,int) ; 
 int /*<<< orphan*/  write_register (struct mxl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cfg_dev_xtal(struct mxl *state, u32 freq, u32 cap, u32 enable)
{
	if (state->base->can_clkout || !enable)
		update_by_mnemonic(state, 0x90200054, 23, 1, enable);

	if (freq == 24000000)
		write_register(state, HYDRA_CRYSTAL_SETTING, 0);
	else
		write_register(state, HYDRA_CRYSTAL_SETTING, 1);

	write_register(state, HYDRA_CRYSTAL_CAP, cap);
}