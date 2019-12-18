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
typedef  int /*<<< orphan*/  u8 ;
struct brcms_hardware {scalar_t__ clk; int /*<<< orphan*/  hw_stf_ss_opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_upd_ofdm_pctl1_table (struct brcms_hardware*) ; 

void brcms_b_band_stf_ss_set(struct brcms_hardware *wlc_hw, u8 stf_mode)
{
	wlc_hw->hw_stf_ss_opmode = stf_mode;

	if (wlc_hw->clk)
		brcms_upd_ofdm_pctl1_table(wlc_hw);
}