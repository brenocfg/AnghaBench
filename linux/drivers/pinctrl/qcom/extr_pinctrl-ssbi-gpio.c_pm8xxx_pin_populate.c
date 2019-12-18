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
struct pm8xxx_pin_data {int power_source; int mode; int open_drain; int output_value; int bias; int pull_up_strength; int output_strength; int disable; int function; int inverted; } ;
struct pm8xxx_gpio {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int PM8XXX_GPIO_BIAS_PU_1P5_30 ; 
 int PM8XXX_GPIO_BIAS_PU_30 ; 
 int pm8xxx_read_bank (struct pm8xxx_gpio*,struct pm8xxx_pin_data*,int) ; 

__attribute__((used)) static int pm8xxx_pin_populate(struct pm8xxx_gpio *pctrl,
			       struct pm8xxx_pin_data *pin)
{
	int val;

	val = pm8xxx_read_bank(pctrl, pin, 0);
	if (val < 0)
		return val;

	pin->power_source = (val >> 1) & 0x7;

	val = pm8xxx_read_bank(pctrl, pin, 1);
	if (val < 0)
		return val;

	pin->mode = (val >> 2) & 0x3;
	pin->open_drain = !!(val & BIT(1));
	pin->output_value = val & BIT(0);

	val = pm8xxx_read_bank(pctrl, pin, 2);
	if (val < 0)
		return val;

	pin->bias = (val >> 1) & 0x7;
	if (pin->bias <= PM8XXX_GPIO_BIAS_PU_1P5_30)
		pin->pull_up_strength = pin->bias;
	else
		pin->pull_up_strength = PM8XXX_GPIO_BIAS_PU_30;

	val = pm8xxx_read_bank(pctrl, pin, 3);
	if (val < 0)
		return val;

	pin->output_strength = (val >> 2) & 0x3;
	pin->disable = val & BIT(0);

	val = pm8xxx_read_bank(pctrl, pin, 4);
	if (val < 0)
		return val;

	pin->function = (val >> 1) & 0x7;

	val = pm8xxx_read_bank(pctrl, pin, 5);
	if (val < 0)
		return val;

	pin->inverted = !(val & BIT(3));

	return 0;
}