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
struct abm {int dmcu_is_running; TYPE_1__ stored_backlight_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_PWM_CNTL ; 
 int /*<<< orphan*/  BL_PWM_CNTL2 ; 
 int /*<<< orphan*/  BL_PWM_PERIOD_CNTL ; 
 int /*<<< orphan*/  BL_PWM_REF_DIV ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_REF_DIV ; 
 int /*<<< orphan*/  MCP_DISABLE_ABM_IMMEDIATELY ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* REG_READ (int /*<<< orphan*/ ) ; 
 struct dce_abm* TO_DCE_ABM (struct abm*) ; 
 int /*<<< orphan*/  dce_abm_set_pipe (struct abm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dce_abm_immediate_disable(struct abm *abm)
{
	struct dce_abm *abm_dce = TO_DCE_ABM(abm);

	if (abm->dmcu_is_running == false)
		return true;

	dce_abm_set_pipe(abm, MCP_DISABLE_ABM_IMMEDIATELY);

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