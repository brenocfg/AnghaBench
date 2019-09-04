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
struct transform {int dummy; } ;
struct dce_transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCFE_MEM_LIGHT_SLEEP_CNTL ; 
 int /*<<< orphan*/  DCFE_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  DCP_LUT_LIGHT_SLEEP_DIS ; 
 int /*<<< orphan*/  DCP_LUT_MEM_PWR_DIS ; 
 int /*<<< orphan*/  DCP_REGAMMA_MEM_PWR_DIS ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGAMMA_LUT_LIGHT_SLEEP_DIS ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 

void dce110_opp_power_on_regamma_lut(struct transform *xfm,
				     bool power_on)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);

	if (REG(DCFE_MEM_PWR_CTRL))
		REG_UPDATE_2(DCFE_MEM_PWR_CTRL,
			     DCP_REGAMMA_MEM_PWR_DIS, power_on,
			     DCP_LUT_MEM_PWR_DIS, power_on);
	else
		REG_UPDATE_2(DCFE_MEM_LIGHT_SLEEP_CNTL,
			    REGAMMA_LUT_LIGHT_SLEEP_DIS, power_on,
			    DCP_LUT_LIGHT_SLEEP_DIS, power_on);

}