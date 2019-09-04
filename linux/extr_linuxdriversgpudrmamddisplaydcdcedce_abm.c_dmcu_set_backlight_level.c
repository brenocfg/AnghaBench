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
typedef  int uint32_t ;
struct dce_abm {int dummy; } ;

/* Variables and functions */
 int ATOM_S2_CURRENT_BL_LEVEL_MASK ; 
 int ATOM_S2_CURRENT_BL_LEVEL_SHIFT ; 
 int /*<<< orphan*/  BIOS_SCRATCH_2 ; 
 int /*<<< orphan*/  BL1_PWM_USER_LEVEL ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG_BYTE0 ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG_BYTE1 ; 
 int /*<<< orphan*/  MASTER_COMM_CNTL_REG ; 
 int /*<<< orphan*/  MASTER_COMM_DATA_REG1 ; 
 int /*<<< orphan*/  MASTER_COMM_INTERRUPT ; 
 int /*<<< orphan*/  MCP_ABM_PIPE_SET ; 
 int MCP_BL_SET ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dmcu_set_backlight_level(
	struct dce_abm *abm_dce,
	uint32_t level,
	uint32_t frame_ramp,
	uint32_t controller_id)
{
	unsigned int backlight_16_bit = (level * 0x10101) >> 8;
	unsigned int backlight_17_bit = backlight_16_bit +
				(((backlight_16_bit & 0x80) >> 7) & 1);
	uint32_t rampingBoundary = 0xFFFF;
	uint32_t s2;

	/* set ramping boundary */
	REG_WRITE(MASTER_COMM_DATA_REG1, rampingBoundary);

	/* setDMCUParam_Pipe */
	REG_UPDATE_2(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, MCP_ABM_PIPE_SET,
			MASTER_COMM_CMD_REG_BYTE1, controller_id);

	/* notifyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* waitDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT,
			0, 1, 80000);

	/* setDMCUParam_BL */
	REG_UPDATE(BL1_PWM_USER_LEVEL, BL1_PWM_USER_LEVEL, backlight_17_bit);

	/* write ramp */
	if (controller_id == 0)
		frame_ramp = 0;
	REG_WRITE(MASTER_COMM_DATA_REG1, frame_ramp);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, MCP_BL_SET);

	/* notifyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* UpdateRequestedBacklightLevel */
	s2 = REG_READ(BIOS_SCRATCH_2);

	s2 &= ~ATOM_S2_CURRENT_BL_LEVEL_MASK;
	level &= (ATOM_S2_CURRENT_BL_LEVEL_MASK >>
				ATOM_S2_CURRENT_BL_LEVEL_SHIFT);
	s2 |= (level << ATOM_S2_CURRENT_BL_LEVEL_SHIFT);

	REG_WRITE(BIOS_SCRATCH_2, s2);
}