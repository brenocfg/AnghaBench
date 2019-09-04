#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dce_abm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV; void* BL_PWM_PERIOD_CNTL; void* BL_PWM_CNTL2; void* BL_PWM_CNTL; } ;
struct abm {TYPE_1__ stored_backlight_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_PWM_CNTL ; 
 int /*<<< orphan*/  BL_PWM_CNTL2 ; 
 int /*<<< orphan*/  BL_PWM_PERIOD_CNTL ; 
 int /*<<< orphan*/  BL_PWM_REF_DIV ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_REF_DIV ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG_BYTE0 ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG_BYTE2 ; 
 int /*<<< orphan*/  MASTER_COMM_CNTL_REG ; 
 int /*<<< orphan*/  MASTER_COMM_INTERRUPT ; 
 int /*<<< orphan*/  MCP_ABM_LEVEL_SET ; 
 int /*<<< orphan*/  MCP_DISABLE_ABM_IMMEDIATELY ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct dce_abm* TO_DCE_ABM (struct abm*) ; 

__attribute__((used)) static bool dce_abm_immediate_disable(struct abm *abm)
{
	struct dce_abm *abm_dce = TO_DCE_ABM(abm);

	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
			1, 80000);

	/* setDMCUParam_ABMLevel */
	REG_UPDATE_2(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, MCP_ABM_LEVEL_SET,
			MASTER_COMM_CMD_REG_BYTE2, MCP_DISABLE_ABM_IMMEDIATELY);

	/* notifyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	abm->stored_backlight_registers.BL_PWM_CNTL =
		REG_READ(BL_PWM_CNTL);
	abm->stored_backlight_registers.BL_PWM_CNTL2 =
		REG_READ(BL_PWM_CNTL2);
	abm->stored_backlight_registers.BL_PWM_PERIOD_CNTL =
		REG_READ(BL_PWM_PERIOD_CNTL);

	REG_GET(LVTMA_PWRSEQ_REF_DIV, BL_PWM_REF_DIV,
		&abm->stored_backlight_registers.LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV);
	return true;
}