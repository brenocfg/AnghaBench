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
struct bq2415x_device {int dummy; } ;
typedef  enum bq2415x_command { ____Placeholder_bq2415x_command } bq2415x_command ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_BIT_BOOST ; 
 int /*<<< orphan*/  BQ2415X_BIT_CE ; 
 int /*<<< orphan*/  BQ2415X_BIT_EN_STAT ; 
 int /*<<< orphan*/  BQ2415X_BIT_HZ_MODE ; 
 int /*<<< orphan*/  BQ2415X_BIT_OPA_MODE ; 
 int /*<<< orphan*/  BQ2415X_BIT_OTG ; 
 int /*<<< orphan*/  BQ2415X_BIT_OTG_EN ; 
 int /*<<< orphan*/  BQ2415X_BIT_OTG_PL ; 
 int /*<<< orphan*/  BQ2415X_BIT_TE ; 
 int /*<<< orphan*/  BQ2415X_BIT_TMR_RST ; 
#define  BQ2415X_BOOST_MODE_DISABLE 156 
#define  BQ2415X_BOOST_MODE_ENABLE 155 
#define  BQ2415X_BOOST_MODE_STATUS 154 
#define  BQ2415X_BOOST_STATUS 153 
#define  BQ2415X_CHARGER_DISABLE 152 
#define  BQ2415X_CHARGER_ENABLE 151 
#define  BQ2415X_CHARGER_STATUS 150 
#define  BQ2415X_CHARGE_STATUS 149 
#define  BQ2415X_CHARGE_TERMINATION_DISABLE 148 
#define  BQ2415X_CHARGE_TERMINATION_ENABLE 147 
#define  BQ2415X_CHARGE_TERMINATION_STATUS 146 
#define  BQ2415X_FAULT_STATUS 145 
#define  BQ2415X_HIGH_IMPEDANCE_DISABLE 144 
#define  BQ2415X_HIGH_IMPEDANCE_ENABLE 143 
#define  BQ2415X_HIGH_IMPEDANCE_STATUS 142 
 int /*<<< orphan*/  BQ2415X_MASK_FAULT ; 
 int /*<<< orphan*/  BQ2415X_MASK_PN ; 
 int /*<<< orphan*/  BQ2415X_MASK_REVISION ; 
 int /*<<< orphan*/  BQ2415X_MASK_STAT ; 
 int /*<<< orphan*/  BQ2415X_MASK_VENDER ; 
#define  BQ2415X_OTG_ACTIVATE_HIGH 141 
#define  BQ2415X_OTG_ACTIVATE_LOW 140 
#define  BQ2415X_OTG_LEVEL 139 
#define  BQ2415X_OTG_PIN_DISABLE 138 
#define  BQ2415X_OTG_PIN_ENABLE 137 
#define  BQ2415X_OTG_PIN_STATUS 136 
#define  BQ2415X_OTG_STATUS 135 
#define  BQ2415X_PART_NUMBER 134 
 int /*<<< orphan*/  BQ2415X_REG_CONTROL ; 
 int /*<<< orphan*/  BQ2415X_REG_STATUS ; 
 int /*<<< orphan*/  BQ2415X_REG_VENDER ; 
 int /*<<< orphan*/  BQ2415X_REG_VOLTAGE ; 
#define  BQ2415X_REVISION 133 
 int /*<<< orphan*/  BQ2415X_SHIFT_FAULT ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_PN ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_REVISION ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_STAT ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_VENDER ; 
#define  BQ2415X_STAT_PIN_DISABLE 132 
#define  BQ2415X_STAT_PIN_ENABLE 131 
#define  BQ2415X_STAT_PIN_STATUS 130 
#define  BQ2415X_TIMER_RESET 129 
#define  BQ2415X_VENDER_CODE 128 
 int EINVAL ; 
 int bq2415x_i2c_read_bit (struct bq2415x_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bq2415x_i2c_read_mask (struct bq2415x_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bq2415x_i2c_write_bit (struct bq2415x_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_exec_command(struct bq2415x_device *bq,
				enum bq2415x_command command)
{
	int ret;

	switch (command) {
	case BQ2415X_TIMER_RESET:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_STATUS,
				1, BQ2415X_BIT_TMR_RST);
	case BQ2415X_OTG_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_STATUS,
				BQ2415X_BIT_OTG);
	case BQ2415X_STAT_PIN_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_STATUS,
				BQ2415X_BIT_EN_STAT);
	case BQ2415X_STAT_PIN_ENABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_STATUS, 1,
				BQ2415X_BIT_EN_STAT);
	case BQ2415X_STAT_PIN_DISABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_STATUS, 0,
				BQ2415X_BIT_EN_STAT);
	case BQ2415X_CHARGE_STATUS:
		return bq2415x_i2c_read_mask(bq, BQ2415X_REG_STATUS,
				BQ2415X_MASK_STAT, BQ2415X_SHIFT_STAT);
	case BQ2415X_BOOST_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_STATUS,
				BQ2415X_BIT_BOOST);
	case BQ2415X_FAULT_STATUS:
		return bq2415x_i2c_read_mask(bq, BQ2415X_REG_STATUS,
			BQ2415X_MASK_FAULT, BQ2415X_SHIFT_FAULT);

	case BQ2415X_CHARGE_TERMINATION_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_CONTROL,
				BQ2415X_BIT_TE);
	case BQ2415X_CHARGE_TERMINATION_ENABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_TE);
	case BQ2415X_CHARGE_TERMINATION_DISABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_TE);
	case BQ2415X_CHARGER_STATUS:
		ret = bq2415x_i2c_read_bit(bq, BQ2415X_REG_CONTROL,
			BQ2415X_BIT_CE);
		if (ret < 0)
			return ret;
		return ret > 0 ? 0 : 1;
	case BQ2415X_CHARGER_ENABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_CE);
	case BQ2415X_CHARGER_DISABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_CE);
	case BQ2415X_HIGH_IMPEDANCE_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_CONTROL,
				BQ2415X_BIT_HZ_MODE);
	case BQ2415X_HIGH_IMPEDANCE_ENABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_HZ_MODE);
	case BQ2415X_HIGH_IMPEDANCE_DISABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_HZ_MODE);
	case BQ2415X_BOOST_MODE_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_CONTROL,
				BQ2415X_BIT_OPA_MODE);
	case BQ2415X_BOOST_MODE_ENABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_OPA_MODE);
	case BQ2415X_BOOST_MODE_DISABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_OPA_MODE);

	case BQ2415X_OTG_LEVEL:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_VOLTAGE,
				BQ2415X_BIT_OTG_PL);
	case BQ2415X_OTG_ACTIVATE_HIGH:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_VOLTAGE,
				1, BQ2415X_BIT_OTG_PL);
	case BQ2415X_OTG_ACTIVATE_LOW:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_VOLTAGE,
				0, BQ2415X_BIT_OTG_PL);
	case BQ2415X_OTG_PIN_STATUS:
		return bq2415x_i2c_read_bit(bq, BQ2415X_REG_VOLTAGE,
				BQ2415X_BIT_OTG_EN);
	case BQ2415X_OTG_PIN_ENABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_VOLTAGE,
				1, BQ2415X_BIT_OTG_EN);
	case BQ2415X_OTG_PIN_DISABLE:
		return bq2415x_i2c_write_bit(bq, BQ2415X_REG_VOLTAGE,
				0, BQ2415X_BIT_OTG_EN);

	case BQ2415X_VENDER_CODE:
		return bq2415x_i2c_read_mask(bq, BQ2415X_REG_VENDER,
			BQ2415X_MASK_VENDER, BQ2415X_SHIFT_VENDER);
	case BQ2415X_PART_NUMBER:
		return bq2415x_i2c_read_mask(bq, BQ2415X_REG_VENDER,
				BQ2415X_MASK_PN, BQ2415X_SHIFT_PN);
	case BQ2415X_REVISION:
		return bq2415x_i2c_read_mask(bq, BQ2415X_REG_VENDER,
			BQ2415X_MASK_REVISION, BQ2415X_SHIFT_REVISION);
	}
	return -EINVAL;
}