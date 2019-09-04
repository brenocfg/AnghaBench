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
struct ucb1x00 {int adc_cr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  UCB_ADC_CR ; 
 unsigned int UCB_ADC_DAT (unsigned int) ; 
 int /*<<< orphan*/  UCB_ADC_DATA ; 
 unsigned int UCB_ADC_DAT_VAL ; 
 int UCB_ADC_START ; 
 int UCB_ADC_SYNC_ENA ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 unsigned int ucb1x00_reg_read (struct ucb1x00*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,int) ; 

unsigned int ucb1x00_adc_read(struct ucb1x00 *ucb, int adc_channel, int sync)
{
	unsigned int val;

	if (sync)
		adc_channel |= UCB_ADC_SYNC_ENA;

	ucb1x00_reg_write(ucb, UCB_ADC_CR, ucb->adc_cr | adc_channel);
	ucb1x00_reg_write(ucb, UCB_ADC_CR, ucb->adc_cr | adc_channel | UCB_ADC_START);

	for (;;) {
		val = ucb1x00_reg_read(ucb, UCB_ADC_DATA);
		if (val & UCB_ADC_DAT_VAL)
			break;
		/* yield to other processes */
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(1);
	}

	return UCB_ADC_DAT(val);
}