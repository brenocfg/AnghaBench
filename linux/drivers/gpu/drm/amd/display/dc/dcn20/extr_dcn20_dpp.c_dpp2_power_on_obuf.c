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
 int /*<<< orphan*/  CM_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  DSCL_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  LUT_MEM_PWR_FORCE ; 
 int /*<<< orphan*/  OBUF_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  OBUF_MEM_PWR_FORCE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHARED_MEM_PWR_DIS ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

void dpp2_power_on_obuf(
		struct dpp *dpp_base,
	bool power_on)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(CM_MEM_PWR_CTRL, SHARED_MEM_PWR_DIS, power_on == true ? 1:0);

	REG_UPDATE(OBUF_MEM_PWR_CTRL,
			OBUF_MEM_PWR_FORCE, power_on == true ? 0:1);

	REG_UPDATE(DSCL_MEM_PWR_CTRL,
			LUT_MEM_PWR_FORCE, power_on == true ? 0:1);
}