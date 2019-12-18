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
struct lpc18xx_pin_caps {scalar_t__ analog; scalar_t__ type; unsigned int* functions; } ;
struct TYPE_2__ {struct lpc18xx_pin_caps* drv_data; } ;

/* Variables and functions */
 scalar_t__ DAC ; 
 unsigned int FUNC_ADC ; 
 unsigned int FUNC_DAC ; 
 unsigned int FUNC_I2C0 ; 
 unsigned int FUNC_USB1 ; 
 int LPC18XX_SCU_FUNC_PER_PIN ; 
 scalar_t__ TYPE_I2C0 ; 
 scalar_t__ TYPE_USB1 ; 
 TYPE_1__* lpc18xx_pins ; 

__attribute__((used)) static bool lpc18xx_valid_pin_function(unsigned pin, unsigned function)
{
	struct lpc18xx_pin_caps *p = lpc18xx_pins[pin].drv_data;
	int i;

	if (function == FUNC_DAC && p->analog == DAC)
		return true;

	if (function == FUNC_ADC && p->analog)
		return true;

	if (function == FUNC_I2C0 && p->type == TYPE_I2C0)
		return true;

	if (function == FUNC_USB1 && p->type == TYPE_USB1)
		return true;

	for (i = 0; i < LPC18XX_SCU_FUNC_PER_PIN; i++) {
		if (function == p->functions[i])
			return true;
	}

	return false;
}