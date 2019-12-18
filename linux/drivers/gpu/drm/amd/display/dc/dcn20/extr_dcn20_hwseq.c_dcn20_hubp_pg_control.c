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
struct dce_hwseq {TYPE_1__* ctx; } ;
struct TYPE_6__ {scalar_t__ disable_hubp_power_gate; } ;
struct TYPE_5__ {TYPE_3__ debug; } ;
struct TYPE_4__ {TYPE_2__* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DOMAIN0_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN0_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN0_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN0_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN2_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN2_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN2_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN2_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN4_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN4_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN4_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN4_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN6_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN6_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN6_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN6_POWER_GATE ; 
 int /*<<< orphan*/  DOMAIN8_PGFSM_PWR_STATUS ; 
 int /*<<< orphan*/  DOMAIN8_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN8_PG_STATUS ; 
 int /*<<< orphan*/  DOMAIN8_POWER_GATE ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void dcn20_hubp_pg_control(
		struct dce_hwseq *hws,
		unsigned int hubp_inst,
		bool power_on)
{
	uint32_t power_gate = power_on ? 0 : 1;
	uint32_t pwr_status = power_on ? 0 : 2;

	if (hws->ctx->dc->debug.disable_hubp_power_gate)
		return;
	if (REG(DOMAIN0_PG_CONFIG) == 0)
		return;

	switch (hubp_inst) {
	case 0: /* DCHUBP0 */
		REG_UPDATE(DOMAIN0_PG_CONFIG,
				DOMAIN0_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN0_PG_STATUS,
				DOMAIN0_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 1: /* DCHUBP1 */
		REG_UPDATE(DOMAIN2_PG_CONFIG,
				DOMAIN2_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN2_PG_STATUS,
				DOMAIN2_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 2: /* DCHUBP2 */
		REG_UPDATE(DOMAIN4_PG_CONFIG,
				DOMAIN4_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN4_PG_STATUS,
				DOMAIN4_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 3: /* DCHUBP3 */
		REG_UPDATE(DOMAIN6_PG_CONFIG,
				DOMAIN6_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN6_PG_STATUS,
				DOMAIN6_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 4: /* DCHUBP4 */
		REG_UPDATE(DOMAIN8_PG_CONFIG,
				DOMAIN8_POWER_GATE, power_gate);

		REG_WAIT(DOMAIN8_PG_STATUS,
				DOMAIN8_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		break;
	case 5: /* DCHUBP5 */
		/*
		 * Do not power gate DCHUB5, should be left at HW default, power on permanently.
		 * PG on Pipe5 is De-featured, attempting to put it to PG state may result in hard
		 * reset.
		 * REG_UPDATE(DOMAIN10_PG_CONFIG,
		 *		DOMAIN10_POWER_GATE, power_gate);
		 *
		 * REG_WAIT(DOMAIN10_PG_STATUS,
		 *		DOMAIN10_PGFSM_PWR_STATUS, pwr_status,
		 *		1, 1000);
		 */
		break;
	default:
		BREAK_TO_DEBUGGER();
		break;
	}
}