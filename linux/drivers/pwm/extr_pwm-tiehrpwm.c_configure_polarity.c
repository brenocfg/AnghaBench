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
typedef  int u16 ;
struct ehrpwm_pwm_chip {scalar_t__* polarity; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 unsigned int AQCTLA ; 
 unsigned int AQCTLB ; 
 int AQCTL_CAU_MASK ; 
 int AQCTL_CBU_MASK ; 
 int AQCTL_CHANA_POLINVERSED ; 
 int AQCTL_CHANA_POLNORMAL ; 
 int AQCTL_CHANB_POLINVERSED ; 
 int AQCTL_CHANB_POLNORMAL ; 
 int AQCTL_PRD_MASK ; 
 int AQCTL_ZRO_MASK ; 
 scalar_t__ PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  ehrpwm_modify (int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static void configure_polarity(struct ehrpwm_pwm_chip *pc, int chan)
{
	u16 aqctl_val, aqctl_mask;
	unsigned int aqctl_reg;

	/*
	 * Configure PWM output to HIGH/LOW level on counter
	 * reaches compare register value and LOW/HIGH level
	 * on counter value reaches period register value and
	 * zero value on counter
	 */
	if (chan == 1) {
		aqctl_reg = AQCTLB;
		aqctl_mask = AQCTL_CBU_MASK;

		if (pc->polarity[chan] == PWM_POLARITY_INVERSED)
			aqctl_val = AQCTL_CHANB_POLINVERSED;
		else
			aqctl_val = AQCTL_CHANB_POLNORMAL;
	} else {
		aqctl_reg = AQCTLA;
		aqctl_mask = AQCTL_CAU_MASK;

		if (pc->polarity[chan] == PWM_POLARITY_INVERSED)
			aqctl_val = AQCTL_CHANA_POLINVERSED;
		else
			aqctl_val = AQCTL_CHANA_POLNORMAL;
	}

	aqctl_mask |= AQCTL_PRD_MASK | AQCTL_ZRO_MASK;
	ehrpwm_modify(pc->mmio_base, aqctl_reg, aqctl_mask, aqctl_val);
}