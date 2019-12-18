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
struct max31856_data {int dummy; } ;
struct iio_chan_spec {int channel2; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  IIO_MOD_TEMP_AMBIENT 129 
#define  IIO_NO_MOD 128 
 int /*<<< orphan*/  MAX31856_CJTO_REG ; 
 int MAX31856_FAULT_OPEN ; 
 int MAX31856_FAULT_OVUV ; 
 int /*<<< orphan*/  MAX31856_LTCBH_REG ; 
 int /*<<< orphan*/  MAX31856_SR_REG ; 
 int max31856_read (struct max31856_data*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int max31856_thermocouple_read(struct max31856_data *data,
				      struct iio_chan_spec const *chan,
				      int *val)
{
	int ret, offset_cjto;
	u8 reg_val[3];

	switch (chan->channel2) {
	case IIO_NO_MOD:
		/*
		 * Multibyte Read
		 * MAX31856_LTCBH_REG, MAX31856_LTCBM_REG, MAX31856_LTCBL_REG
		 */
		ret = max31856_read(data, MAX31856_LTCBH_REG, reg_val, 3);
		if (ret)
			return ret;
		/* Skip last 5 dead bits of LTCBL */
		*val = (reg_val[0] << 16 | reg_val[1] << 8 | reg_val[2]) >> 5;
		/* Check 7th bit of LTCBH reg. value for sign*/
		if (reg_val[0] & 0x80)
			*val -= 0x80000;
		break;

	case IIO_MOD_TEMP_AMBIENT:
		/*
		 * Multibyte Read
		 * MAX31856_CJTO_REG, MAX31856_CJTH_REG, MAX31856_CJTL_REG
		 */
		ret = max31856_read(data, MAX31856_CJTO_REG, reg_val, 3);
		if (ret)
			return ret;
		/* Get Cold Junction Temp. offset register value */
		offset_cjto = reg_val[0];
		/* Get CJTH and CJTL value and skip last 2 dead bits of CJTL */
		*val = (reg_val[1] << 8 | reg_val[2]) >> 2;
		/* As per datasheet add offset into CJTH and CJTL */
		*val += offset_cjto;
		/* Check 7th bit of CJTH reg. value for sign */
		if (reg_val[1] & 0x80)
			*val -= 0x4000;
		break;

	default:
		return -EINVAL;
	}

	ret = max31856_read(data, MAX31856_SR_REG, reg_val, 1);
	if (ret)
		return ret;
	/* Check for over/under voltage or open circuit fault */
	if (reg_val[0] & (MAX31856_FAULT_OVUV | MAX31856_FAULT_OPEN))
		return -EIO;

	return ret;
}