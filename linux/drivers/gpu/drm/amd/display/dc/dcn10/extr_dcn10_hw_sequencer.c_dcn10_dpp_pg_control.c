#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct dce_hwseq {TYPE_3__* ctx; } ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct TYPE_4__ {scalar_t__ disable_dpp_power_gate; } ;
struct TYPE_5__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DOMAIN1_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN1_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN1_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN1_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN3_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN3_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN3_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN3_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN5_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN5_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN5_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN5_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN7_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN7_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN7_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN7_POWER_GATE ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void dcn10_dpp_pg_control(
		struct dce_hwseq *hws,
		unsigned int dpp_inst,
		bool power_on)
{
	uint32_t power_gate = power_on ? 0 : 1;
	uint32_t pwr_status = power_on ? 0 : 2;

	if (hws->ctx->dc->debug.disable_dpp_power_gate)
		return;
	if (REG(DOMAIN1_PG_CONFIG) == 0)
		return;

	switch (dpp_inst) {
	case 0: /* DPP0 */
		REG_UPDATE(DOMAIN1_PG_CONFIG,
				DOMAIN1_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN1_PG_STATUS,
				DOMAIN1_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 1: /* DPP1 */
		REG_UPDATE(DOMAIN3_PG_CONFIG,
				DOMAIN3_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN3_PG_STATUS,
				DOMAIN3_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 2: /* DPP2 */
		REG_UPDATE(DOMAIN5_PG_CONFIG,
				DOMAIN5_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN5_PG_STATUS,
				DOMAIN5_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 3: /* DPP3 */
		REG_UPDATE(DOMAIN7_PG_CONFIG,
				DOMAIN7_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN7_PG_STATUS,
				DOMAIN7_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	default:
		BREAK_TO_DEBUGGER();
		break;
	}
}