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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct da9055_hwmon {int /*<<< orphan*/  da9055; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_ADC_TJUNC ; 
 int /*<<< orphan*/  DA9055_REG_T_OFFSET ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int da9055_adc_manual_read (struct da9055_hwmon*,int /*<<< orphan*/ ) ; 
 int da9055_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9055_hwmon* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t da9055_tjunc_show(struct device *dev,
				 struct device_attribute *devattr, char *buf)
{
	struct da9055_hwmon *hwmon = dev_get_drvdata(dev);
	int tjunc;
	int toffset;

	tjunc = da9055_adc_manual_read(hwmon, DA9055_ADC_TJUNC);
	if (tjunc < 0)
		return tjunc;

	toffset = da9055_reg_read(hwmon->da9055, DA9055_REG_T_OFFSET);
	if (toffset < 0)
		return toffset;

	/*
	 * Degrees celsius = -0.4084 * (ADC_RES - T_OFFSET) + 307.6332
	 * T_OFFSET is a trim value used to improve accuracy of the result
	 */
	return sprintf(buf, "%d\n", DIV_ROUND_CLOSEST(-4084 * (tjunc - toffset)
							+ 3076332, 10000));
}