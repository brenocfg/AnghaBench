#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pm8xxx_pin_data {int mode; int input; int output; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_mpp {TYPE_2__ desc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PM8XXX_MPP_ANALOG 130 
#define  PM8XXX_MPP_DIGITAL 129 
#define  PM8XXX_MPP_SINK 128 
 struct pm8xxx_mpp* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pm8xxx_mpp_update (struct pm8xxx_mpp*,struct pm8xxx_pin_data*) ; 

__attribute__((used)) static int pm8xxx_mpp_direction_input(struct gpio_chip *chip,
				       unsigned offset)
{
	struct pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	switch (pin->mode) {
	case PM8XXX_MPP_DIGITAL:
		pin->input = true;
		break;
	case PM8XXX_MPP_ANALOG:
		pin->input = true;
		pin->output = true;
		break;
	case PM8XXX_MPP_SINK:
		return -EINVAL;
	}

	pm8xxx_mpp_update(pctrl, pin);

	return 0;
}