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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_ADC_CR ; 
 int /*<<< orphan*/  UCB_ADC_DATA ; 
 unsigned int UCB_ADC_DAT_MASK ; 
 unsigned int UCB_ADC_DAT_VALID ; 
 int UCB_ADC_ENA ; 
 int UCB_ADC_START ; 
 int UCB_ADC_SYNC_ENA ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 unsigned int ucb1400_reg_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_reg_write (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

unsigned int ucb1400_adc_read(struct snd_ac97 *ac97, u16 adc_channel,
		int adcsync)
{
	unsigned int val;

	if (adcsync)
		adc_channel |= UCB_ADC_SYNC_ENA;

	ucb1400_reg_write(ac97, UCB_ADC_CR, UCB_ADC_ENA | adc_channel);
	ucb1400_reg_write(ac97, UCB_ADC_CR, UCB_ADC_ENA | adc_channel |
			UCB_ADC_START);

	while (!((val = ucb1400_reg_read(ac97, UCB_ADC_DATA))
				& UCB_ADC_DAT_VALID))
		schedule_timeout_uninterruptible(1);

	return val & UCB_ADC_DAT_MASK;
}