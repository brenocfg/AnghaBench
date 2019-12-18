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
typedef  int /*<<< orphan*/  u8 ;
struct da9052_hwmon {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
#define  DA9052_ADC_TSI_XN 131 
#define  DA9052_ADC_TSI_XP 130 
#define  DA9052_ADC_TSI_YN 129 
#define  DA9052_ADC_TSI_YP 128 
 int /*<<< orphan*/  DA9052_TSICONTB_TSIMAN ; 
 int /*<<< orphan*/  DA9052_TSICONTB_TSIMUX_XN ; 
 int /*<<< orphan*/  DA9052_TSICONTB_TSIMUX_XP ; 
 int /*<<< orphan*/  DA9052_TSICONTB_TSIMUX_YN ; 
 int /*<<< orphan*/  DA9052_TSICONTB_TSIMUX_YP ; 
 int /*<<< orphan*/  DA9052_TSI_CONT_B_REG ; 
 int da9052_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9052_request_tsi_read(struct da9052_hwmon *hwmon, int channel)
{
	u8 val = DA9052_TSICONTB_TSIMAN;

	switch (channel) {
	case DA9052_ADC_TSI_XP:
		val |= DA9052_TSICONTB_TSIMUX_XP;
		break;
	case DA9052_ADC_TSI_YP:
		val |= DA9052_TSICONTB_TSIMUX_YP;
		break;
	case DA9052_ADC_TSI_XN:
		val |= DA9052_TSICONTB_TSIMUX_XN;
		break;
	case DA9052_ADC_TSI_YN:
		val |= DA9052_TSICONTB_TSIMUX_YN;
		break;
	}

	return da9052_reg_write(hwmon->da9052, DA9052_TSI_CONT_B_REG, val);
}