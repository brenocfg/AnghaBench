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
typedef  int u16 ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ecap_pwm_chip {scalar_t__ mmio_base; TYPE_1__ chip; } ;

/* Variables and functions */
 scalar_t__ ECCTL2 ; 
 int ECCTL2_APWM_MODE ; 
 int ECCTL2_TSCTR_FREERUN ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 struct ecap_pwm_chip* to_ecap_pwm_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int ecap_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 value;

	/* Leave clock enabled on enabling PWM */
	pm_runtime_get_sync(pc->chip.dev);

	/*
	 * Enable 'Free run Time stamp counter mode' to start counter
	 * and  'APWM mode' to enable APWM output
	 */
	value = readw(pc->mmio_base + ECCTL2);
	value |= ECCTL2_TSCTR_FREERUN | ECCTL2_APWM_MODE;
	writew(value, pc->mmio_base + ECCTL2);

	return 0;
}