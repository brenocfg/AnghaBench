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
struct da9150_gpadc {int dummy; } ;

/* Variables and functions */
#define  DA9150_GPADC_CHAN_GPIOA 134 
#define  DA9150_GPADC_CHAN_GPIOB 133 
#define  DA9150_GPADC_CHAN_GPIOC 132 
#define  DA9150_GPADC_CHAN_GPIOD 131 
#define  DA9150_GPADC_CHAN_IBUS 130 
#define  DA9150_GPADC_CHAN_VBUS 129 
#define  DA9150_GPADC_CHAN_VSYS 128 
 int IIO_VAL_INT ; 
 int da9150_gpadc_gpio_6v_voltage_now (int) ; 
 int da9150_gpadc_ibus_current_avg (int) ; 
 int da9150_gpadc_read_adc (struct da9150_gpadc*,int) ; 
 int da9150_gpadc_vbus_21v_voltage_now (int) ; 
 int da9150_gpadc_vsys_6v_voltage_now (int) ; 

__attribute__((used)) static int da9150_gpadc_read_processed(struct da9150_gpadc *gpadc, int channel,
				       int hw_chan, int *val)
{
	int raw_val;

	raw_val = da9150_gpadc_read_adc(gpadc, hw_chan);
	if (raw_val < 0)
		return raw_val;

	switch (channel) {
	case DA9150_GPADC_CHAN_GPIOA:
	case DA9150_GPADC_CHAN_GPIOB:
	case DA9150_GPADC_CHAN_GPIOC:
	case DA9150_GPADC_CHAN_GPIOD:
		*val = da9150_gpadc_gpio_6v_voltage_now(raw_val);
		break;
	case DA9150_GPADC_CHAN_IBUS:
		*val = da9150_gpadc_ibus_current_avg(raw_val);
		break;
	case DA9150_GPADC_CHAN_VBUS:
		*val = da9150_gpadc_vbus_21v_voltage_now(raw_val);
		break;
	case DA9150_GPADC_CHAN_VSYS:
		*val = da9150_gpadc_vsys_6v_voltage_now(raw_val);
		break;
	default:
		/* No processing for other channels so return raw value */
		*val = raw_val;
		break;
	}

	return IIO_VAL_INT;
}