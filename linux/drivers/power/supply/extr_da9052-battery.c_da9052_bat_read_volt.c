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
struct da9052_battery {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_ADC_MAN_MUXSEL_VBAT ; 
 int da9052_adc_manual_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int volt_reg_to_mV (int) ; 

__attribute__((used)) static int da9052_bat_read_volt(struct da9052_battery *bat, int *volt_mV)
{
	int volt;

	volt = da9052_adc_manual_read(bat->da9052, DA9052_ADC_MAN_MUXSEL_VBAT);
	if (volt < 0)
		return volt;

	*volt_mV = volt_reg_to_mV(volt);

	return 0;
}