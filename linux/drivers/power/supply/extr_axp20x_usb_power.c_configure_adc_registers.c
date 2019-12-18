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
struct axp20x_usb_power {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_ADC_EN1 ; 
 int AXP20X_ADC_EN1_VBUS_CURR ; 
 int AXP20X_ADC_EN1_VBUS_VOLT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int configure_adc_registers(struct axp20x_usb_power *power)
{
	/* Enable vbus voltage and current measurement */
	return regmap_update_bits(power->regmap, AXP20X_ADC_EN1,
				  AXP20X_ADC_EN1_VBUS_CURR |
				  AXP20X_ADC_EN1_VBUS_VOLT,
				  AXP20X_ADC_EN1_VBUS_CURR |
				  AXP20X_ADC_EN1_VBUS_VOLT);
}