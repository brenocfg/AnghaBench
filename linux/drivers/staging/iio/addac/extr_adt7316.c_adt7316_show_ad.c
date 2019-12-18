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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int config2; int id; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ADT7316_AD_MSB_DATA_BASE ; 
#define  ADT7316_AD_SINGLE_CH_IN 129 
 int ADT7316_AD_SINGLE_CH_MODE ; 
#define  ADT7316_AD_SINGLE_CH_VDD 128 
 int /*<<< orphan*/  ADT7316_LSB_EX_TEMP_AIN ; 
 int ADT7316_LSB_EX_TEMP_MASK ; 
 int ADT7316_LSB_IN_TEMP_MASK ; 
 int /*<<< orphan*/  ADT7316_LSB_IN_TEMP_VDD ; 
 int ADT7316_LSB_VDD_MASK ; 
 int ADT7316_LSB_VDD_OFFSET ; 
 scalar_t__ ADT7316_MSB_EX_TEMP ; 
 int ADT7316_T_VALUE_FLOAT_MASK ; 
 int ADT7316_T_VALUE_FLOAT_OFFSET ; 
 int ADT7316_T_VALUE_SIGN ; 
 int ADT7516_AD_SINGLE_CH_MASK ; 
 int ADT7516_LSB_AIN_SHIFT ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EPERM ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,...) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t adt7316_show_ad(struct adt7316_chip_info *chip,
			       int channel, char *buf)
{
	u16 data;
	u8 msb, lsb;
	char sign = ' ';
	int ret;

	if ((chip->config2 & ADT7316_AD_SINGLE_CH_MODE) &&
	    channel != (chip->config2 & ADT7516_AD_SINGLE_CH_MASK))
		return -EPERM;

	switch (channel) {
	case ADT7316_AD_SINGLE_CH_IN:
		ret = chip->bus.read(chip->bus.client,
			ADT7316_LSB_IN_TEMP_VDD, &lsb);
		if (ret)
			return -EIO;

		ret = chip->bus.read(chip->bus.client,
			ADT7316_AD_MSB_DATA_BASE + channel, &msb);
		if (ret)
			return -EIO;

		data = msb << ADT7316_T_VALUE_FLOAT_OFFSET;
		data |= lsb & ADT7316_LSB_IN_TEMP_MASK;
		break;
	case ADT7316_AD_SINGLE_CH_VDD:
		ret = chip->bus.read(chip->bus.client,
			ADT7316_LSB_IN_TEMP_VDD, &lsb);
		if (ret)
			return -EIO;

		ret = chip->bus.read(chip->bus.client,

			ADT7316_AD_MSB_DATA_BASE + channel, &msb);
		if (ret)
			return -EIO;

		data = msb << ADT7316_T_VALUE_FLOAT_OFFSET;
		data |= (lsb & ADT7316_LSB_VDD_MASK) >> ADT7316_LSB_VDD_OFFSET;
		return sprintf(buf, "%d\n", data);
	default: /* ex_temp and ain */
		ret = chip->bus.read(chip->bus.client,
			ADT7316_LSB_EX_TEMP_AIN, &lsb);
		if (ret)
			return -EIO;

		ret = chip->bus.read(chip->bus.client,
			ADT7316_AD_MSB_DATA_BASE + channel, &msb);
		if (ret)
			return -EIO;

		data = msb << ADT7316_T_VALUE_FLOAT_OFFSET;
		data |= lsb & (ADT7316_LSB_EX_TEMP_MASK <<
			(ADT7516_LSB_AIN_SHIFT * (channel -
			(ADT7316_MSB_EX_TEMP - ADT7316_AD_MSB_DATA_BASE))));

		if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
			return sprintf(buf, "%d\n", data);

		break;
	}

	if (data & ADT7316_T_VALUE_SIGN) {
		/* convert supplement to positive value */
		data = (ADT7316_T_VALUE_SIGN << 1) - data;
		sign = '-';
	}

	return sprintf(buf, "%c%d.%.2d\n", sign,
		(data >> ADT7316_T_VALUE_FLOAT_OFFSET),
		(data & ADT7316_T_VALUE_FLOAT_MASK) * 25);
}