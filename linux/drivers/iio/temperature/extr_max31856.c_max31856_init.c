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
struct max31856_data {int /*<<< orphan*/  thermocouple_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX31856_CR0_1SHOT ; 
 int /*<<< orphan*/  MAX31856_CR0_AUTOCONVERT ; 
 int /*<<< orphan*/  MAX31856_CR0_OCFAULT ; 
 int /*<<< orphan*/  MAX31856_CR0_OCFAULT_MASK ; 
 int /*<<< orphan*/  MAX31856_CR0_REG ; 
 int /*<<< orphan*/  MAX31856_CR1_REG ; 
 int /*<<< orphan*/  MAX31856_TC_TYPE_MASK ; 
 int max31856_read (struct max31856_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int max31856_write (struct max31856_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max31856_init(struct max31856_data *data)
{
	int ret;
	u8 reg_cr0_val, reg_cr1_val;

	/* Start by changing to Off mode before making changes as
	 * some settings are recommended to be set only when the device
	 * is off
	 */
	ret = max31856_read(data, MAX31856_CR0_REG, &reg_cr0_val, 1);
	if (ret)
		return ret;

	reg_cr0_val &= ~MAX31856_CR0_AUTOCONVERT;
	ret = max31856_write(data, MAX31856_CR0_REG, reg_cr0_val);
	if (ret)
		return ret;

	/* Set thermocouple type based on dts property */
	ret = max31856_read(data, MAX31856_CR1_REG, &reg_cr1_val, 1);
	if (ret)
		return ret;

	reg_cr1_val &= ~MAX31856_TC_TYPE_MASK;
	reg_cr1_val |= data->thermocouple_type;
	ret = max31856_write(data, MAX31856_CR1_REG, reg_cr1_val);
	if (ret)
		return ret;

	/*
	 * Enable Open circuit fault detection
	 * Read datasheet for more information: Table 4.
	 * Value 01 means : Enabled (Once every 16 conversions)
	 */
	reg_cr0_val &= ~MAX31856_CR0_OCFAULT_MASK;
	reg_cr0_val |= MAX31856_CR0_OCFAULT;

	/* Set Auto Conversion Mode */
	reg_cr0_val &= ~MAX31856_CR0_1SHOT;
	reg_cr0_val |= MAX31856_CR0_AUTOCONVERT;

	return max31856_write(data, MAX31856_CR0_REG, reg_cr0_val);
}