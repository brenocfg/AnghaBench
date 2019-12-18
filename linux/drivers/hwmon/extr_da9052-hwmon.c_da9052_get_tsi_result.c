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
typedef  int u8 ;
struct da9052_hwmon {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
#define  DA9052_ADC_TSI_XN 131 
#define  DA9052_ADC_TSI_XP 130 
#define  DA9052_ADC_TSI_YN 129 
#define  DA9052_ADC_TSI_YP 128 
 int DA9052_TSILSB_TSIXL ; 
 int DA9052_TSILSB_TSIXL_BITS ; 
 int DA9052_TSILSB_TSIXL_SHIFT ; 
 int DA9052_TSILSB_TSIYL ; 
 int DA9052_TSILSB_TSIYL_BITS ; 
 int DA9052_TSILSB_TSIYL_SHIFT ; 
 int /*<<< orphan*/  DA9052_TSI_X_MSB_REG ; 
 int EINVAL ; 
 int da9052_group_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int da9052_get_tsi_result(struct da9052_hwmon *hwmon, int channel)
{
	u8 regs[3];
	int msb, lsb, err;

	/* block read to avoid separation of MSB and LSB */
	err = da9052_group_read(hwmon->da9052, DA9052_TSI_X_MSB_REG,
				ARRAY_SIZE(regs), regs);
	if (err)
		return err;

	switch (channel) {
	case DA9052_ADC_TSI_XP:
	case DA9052_ADC_TSI_XN:
		msb = regs[0] << DA9052_TSILSB_TSIXL_BITS;
		lsb = regs[2] & DA9052_TSILSB_TSIXL;
		lsb >>= DA9052_TSILSB_TSIXL_SHIFT;
		break;
	case DA9052_ADC_TSI_YP:
	case DA9052_ADC_TSI_YN:
		msb = regs[1] << DA9052_TSILSB_TSIYL_BITS;
		lsb = regs[2] & DA9052_TSILSB_TSIYL;
		lsb >>= DA9052_TSILSB_TSIYL_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	return msb | lsb;
}