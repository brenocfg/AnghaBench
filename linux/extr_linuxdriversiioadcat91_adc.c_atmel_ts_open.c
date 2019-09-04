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
struct input_dev {int dummy; } ;
struct at91_adc_state {TYPE_1__* caps; } ;
struct TYPE_2__ {scalar_t__ has_tsmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91RL_ADC_IER_PEN ; 
 int /*<<< orphan*/  AT91_ADC_IER ; 
 int /*<<< orphan*/  AT91_ADC_IER_PEN ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct at91_adc_state* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int atmel_ts_open(struct input_dev *dev)
{
	struct at91_adc_state *st = input_get_drvdata(dev);

	if (st->caps->has_tsmr)
		at91_adc_writel(st, AT91_ADC_IER, AT91_ADC_IER_PEN);
	else
		at91_adc_writel(st, AT91_ADC_IER, AT91RL_ADC_IER_PEN);
	return 0;
}