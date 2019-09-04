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
typedef  int uint32_t ;
struct dce_abm {int dummy; } ;
struct TYPE_2__ {scalar_t__ BL_PWM_CNTL; int BL_PWM_CNTL2; int BL_PWM_PERIOD_CNTL; int LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV; } ;
struct abm {TYPE_1__ stored_backlight_registers; } ;

/* Variables and functions */
 int ATOM_S2_VRI_BRIGHT_ENABLE ; 
 int /*<<< orphan*/  BIOS_SCRATCH_2 ; 
 int /*<<< orphan*/  BL_ACTIVE_INT_FRAC_CNT ; 
 int /*<<< orphan*/  BL_PWM_CNTL ; 
 int /*<<< orphan*/  BL_PWM_CNTL2 ; 
 int /*<<< orphan*/  BL_PWM_EN ; 
 int /*<<< orphan*/  BL_PWM_GRP1_REG_LOCK ; 
 int /*<<< orphan*/  BL_PWM_PERIOD_CNTL ; 
 int /*<<< orphan*/  BL_PWM_REF_DIV ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_REF_DIV ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 void* REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 struct dce_abm* TO_DCE_ABM (struct abm*) ; 

__attribute__((used)) static bool dce_abm_init_backlight(struct abm *abm)
{
	struct dce_abm *abm_dce = TO_DCE_ABM(abm);
	uint32_t value;

	/* It must not be 0, so we have to restore them
	 * Bios bug w/a - period resets to zero,
	 * restoring to cache values which is always correct
	 */
	REG_GET(BL_PWM_CNTL, BL_ACTIVE_INT_FRAC_CNT, &value);
	if (value == 0 || value == 1) {
		if (abm->stored_backlight_registers.BL_PWM_CNTL != 0) {
			REG_WRITE(BL_PWM_CNTL,
				abm->stored_backlight_registers.BL_PWM_CNTL);
			REG_WRITE(BL_PWM_CNTL2,
				abm->stored_backlight_registers.BL_PWM_CNTL2);
			REG_WRITE(BL_PWM_PERIOD_CNTL,
				abm->stored_backlight_registers.BL_PWM_PERIOD_CNTL);
			REG_UPDATE(LVTMA_PWRSEQ_REF_DIV,
				BL_PWM_REF_DIV,
				abm->stored_backlight_registers.
				LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV);
		} else {
			/* TODO: Note: This should not really happen since VBIOS
			 * should have initialized PWM registers on boot.
			 */
			REG_WRITE(BL_PWM_CNTL, 0xC000FA00);
			REG_WRITE(BL_PWM_PERIOD_CNTL, 0x000C0FA0);
		}
	} else {
		abm->stored_backlight_registers.BL_PWM_CNTL =
				REG_READ(BL_PWM_CNTL);
		abm->stored_backlight_registers.BL_PWM_CNTL2 =
				REG_READ(BL_PWM_CNTL2);
		abm->stored_backlight_registers.BL_PWM_PERIOD_CNTL =
				REG_READ(BL_PWM_PERIOD_CNTL);

		REG_GET(LVTMA_PWRSEQ_REF_DIV, BL_PWM_REF_DIV,
				&abm->stored_backlight_registers.
				LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV);
	}

	/* Have driver take backlight control
	 * TakeBacklightControl(true)
	 */
	value = REG_READ(BIOS_SCRATCH_2);
	value |= ATOM_S2_VRI_BRIGHT_ENABLE;
	REG_WRITE(BIOS_SCRATCH_2, value);

	/* Enable the backlight output */
	REG_UPDATE(BL_PWM_CNTL, BL_PWM_EN, 1);

	/* Unlock group 2 backlight registers */
	REG_UPDATE(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_REG_LOCK, 0);

	return true;
}