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

/* Variables and functions */
 int /*<<< orphan*/  ANADIG_ANA_MISC0 ; 
 int ANADIG_REG_2P5 ; 
 int BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG ; 
 int /*<<< orphan*/  BM_ANADIG_REG_2P5_ENABLE_WEAK_LINREG ; 
 scalar_t__ REG_CLR ; 
 scalar_t__ REG_SET ; 
 int /*<<< orphan*/  anatop ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_anatop_enable_weak2p5(bool enable)
{
	u32 reg, val;

	regmap_read(anatop, ANADIG_ANA_MISC0, &val);

	/* can only be enabled when stop_mode_config is clear. */
	reg = ANADIG_REG_2P5;
	reg += (enable && (val & BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG) == 0) ?
		REG_SET : REG_CLR;
	regmap_write(anatop, reg, BM_ANADIG_REG_2P5_ENABLE_WEAK_LINREG);
}