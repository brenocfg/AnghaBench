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
struct dcn20_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLNDGAM_MEM_PWR_FORCE ; 
 int /*<<< orphan*/  CM_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_power_on_blnd_lut(
	struct dpp *dpp_base,
	bool power_on)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_SET(CM_MEM_PWR_CTRL, 0,
			BLNDGAM_MEM_PWR_FORCE, power_on == true ? 0:1);

}