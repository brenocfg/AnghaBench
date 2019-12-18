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
struct pp_hwmgr {int dummy; } ;
typedef  enum BACO_STATE { ____Placeholder_BACO_STATE } BACO_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BACO_STATE_IN ; 
 int BACO_STATE_OUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_EnterBaco ; 
 int /*<<< orphan*/  clean_baco_tbl ; 
 int /*<<< orphan*/  enter_baco_tbl ; 
 int /*<<< orphan*/  exit_baco_tbl ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pre_baco_tbl ; 
 int /*<<< orphan*/  smu9_baco_get_state (struct pp_hwmgr*,int*) ; 
 scalar_t__ smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 scalar_t__ soc15_baco_program_registers (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vega10_baco_set_state(struct pp_hwmgr *hwmgr, enum BACO_STATE state)
{
	enum BACO_STATE cur_state;

	smu9_baco_get_state(hwmgr, &cur_state);

	if (cur_state == state)
		/* aisc already in the target state */
		return 0;

	if (state == BACO_STATE_IN) {
		if (soc15_baco_program_registers(hwmgr, pre_baco_tbl,
					     ARRAY_SIZE(pre_baco_tbl))) {
			if (smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnterBaco))
				return -EINVAL;

			if (soc15_baco_program_registers(hwmgr, enter_baco_tbl,
						   ARRAY_SIZE(enter_baco_tbl)))
				return 0;
		}
	} else if (state == BACO_STATE_OUT) {
		/* HW requires at least 20ms between regulator off and on */
		msleep(20);
		/* Execute Hardware BACO exit sequence */
		if (soc15_baco_program_registers(hwmgr, exit_baco_tbl,
					     ARRAY_SIZE(exit_baco_tbl))) {
			if (soc15_baco_program_registers(hwmgr, clean_baco_tbl,
						     ARRAY_SIZE(clean_baco_tbl)))
				return 0;
		}
	}

	return -EINVAL;
}