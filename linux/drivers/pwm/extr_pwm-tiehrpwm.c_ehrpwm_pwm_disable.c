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
typedef  int /*<<< orphan*/  u16 ;
struct pwm_device {scalar_t__ hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct ehrpwm_pwm_chip {int /*<<< orphan*/  tbclk; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQCSFRC ; 
 int /*<<< orphan*/  AQCSFRC_CSFA_FRCLOW ; 
 int /*<<< orphan*/  AQCSFRC_CSFA_MASK ; 
 int /*<<< orphan*/  AQCSFRC_CSFB_FRCLOW ; 
 int /*<<< orphan*/  AQCSFRC_CSFB_MASK ; 
 int /*<<< orphan*/  AQSFRC ; 
 int /*<<< orphan*/  AQSFRC_RLDCSF_IMDT ; 
 int /*<<< orphan*/  AQSFRC_RLDCSF_MASK ; 
 int /*<<< orphan*/  AQSFRC_RLDCSF_ZRO ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehrpwm_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct ehrpwm_pwm_chip* to_ehrpwm_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void ehrpwm_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);
	u16 aqcsfrc_val, aqcsfrc_mask;

	/* Action Qualifier puts PWM output low forcefully */
	if (pwm->hwpwm) {
		aqcsfrc_val = AQCSFRC_CSFB_FRCLOW;
		aqcsfrc_mask = AQCSFRC_CSFB_MASK;
	} else {
		aqcsfrc_val = AQCSFRC_CSFA_FRCLOW;
		aqcsfrc_mask = AQCSFRC_CSFA_MASK;
	}

	/* Update shadow register first before modifying active register */
	ehrpwm_modify(pc->mmio_base, AQSFRC, AQSFRC_RLDCSF_MASK,
		      AQSFRC_RLDCSF_ZRO);
	ehrpwm_modify(pc->mmio_base, AQCSFRC, aqcsfrc_mask, aqcsfrc_val);
	/*
	 * Changes to immediate action on Action Qualifier. This puts
	 * Action Qualifier control on PWM output from next TBCLK
	 */
	ehrpwm_modify(pc->mmio_base, AQSFRC, AQSFRC_RLDCSF_MASK,
		      AQSFRC_RLDCSF_IMDT);

	ehrpwm_modify(pc->mmio_base, AQCSFRC, aqcsfrc_mask, aqcsfrc_val);

	/* Disabling TBCLK on PWM disable */
	clk_disable(pc->tbclk);

	/* Disable clock on PWM disable */
	pm_runtime_put_sync(chip->dev);
}