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
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RGAM_MEM_PWR_FORCE ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_cm_power_on_regamma_lut(struct dpp *dpp_base,
				  bool power_on)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_SET(CM_MEM_PWR_CTRL, 0,
		RGAM_MEM_PWR_FORCE, power_on == true ? 0:1);

}