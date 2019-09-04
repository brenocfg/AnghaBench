#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int num_lanes; int rate; } ;
struct TYPE_3__ {TYPE_2__ base; scalar_t__ spread; scalar_t__ coding8b10b; scalar_t__ scrambler_dis; } ;
struct tc_data {TYPE_1__ link; } ;

/* Variables and functions */
 int DP0_SRCCTRL_BW27 ; 
 int DP0_SRCCTRL_EN810B ; 
 int DP0_SRCCTRL_LANESKEW ; 
 int DP0_SRCCTRL_LANES_2 ; 
 int DP0_SRCCTRL_NOTP ; 
 int DP0_SRCCTRL_SCRMBLDIS ; 
 int DP0_SRCCTRL_SSCG ; 

__attribute__((used)) static u32 tc_srcctrl(struct tc_data *tc)
{
	/*
	 * No training pattern, skew lane 1 data by two LSCLK cycles with
	 * respect to lane 0 data, AutoCorrect Mode = 0
	 */
	u32 reg = DP0_SRCCTRL_NOTP | DP0_SRCCTRL_LANESKEW;

	if (tc->link.scrambler_dis)
		reg |= DP0_SRCCTRL_SCRMBLDIS;	/* Scrambler Disabled */
	if (tc->link.coding8b10b)
		/* Enable 8/10B Encoder (TxData[19:16] not used) */
		reg |= DP0_SRCCTRL_EN810B;
	if (tc->link.spread)
		reg |= DP0_SRCCTRL_SSCG;	/* Spread Spectrum Enable */
	if (tc->link.base.num_lanes == 2)
		reg |= DP0_SRCCTRL_LANES_2;	/* Two Main Channel Lanes */
	if (tc->link.base.rate != 162000)
		reg |= DP0_SRCCTRL_BW27;	/* 2.7 Gbps link */
	return reg;
}