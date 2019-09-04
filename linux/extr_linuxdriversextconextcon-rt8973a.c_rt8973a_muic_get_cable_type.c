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
struct rt8973a_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  RT8973A_MUIC_ADC_OPEN 128 
 int RT8973A_MUIC_ADC_TA ; 
 int RT8973A_MUIC_ADC_USB ; 
 int /*<<< orphan*/  RT8973A_REG_ADC ; 
 unsigned int RT8973A_REG_ADC_MASK ; 
 int /*<<< orphan*/  RT8973A_REG_DEV1 ; 
 unsigned int RT8973A_REG_DEV1_DCPORT_MASK ; 
 unsigned int RT8973A_REG_DEV1_USB_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int rt8973a_muic_get_cable_type(struct rt8973a_muic_info *info)
{
	unsigned int adc, dev1;
	int ret, cable_type;

	/* Read ADC value according to external cable or button */
	ret = regmap_read(info->regmap, RT8973A_REG_ADC, &adc);
	if (ret) {
		dev_err(info->dev, "failed to read ADC register\n");
		return ret;
	}
	cable_type = adc & RT8973A_REG_ADC_MASK;

	/* Read Device 1 reigster to identify correct cable type */
	ret = regmap_read(info->regmap, RT8973A_REG_DEV1, &dev1);
	if (ret) {
		dev_err(info->dev, "failed to read DEV1 register\n");
		return ret;
	}

	switch (adc) {
	case RT8973A_MUIC_ADC_OPEN:
		if (dev1 & RT8973A_REG_DEV1_USB_MASK)
			cable_type = RT8973A_MUIC_ADC_USB;
		else if (dev1 & RT8973A_REG_DEV1_DCPORT_MASK)
			cable_type = RT8973A_MUIC_ADC_TA;
		else
			cable_type = RT8973A_MUIC_ADC_OPEN;
		break;
	default:
		break;
	}

	return cable_type;
}