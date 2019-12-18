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
struct pmbus_driver_info {int dummy; } ;
struct ltc2978_data {int* vout_max; int /*<<< orphan*/ * temp_max; int /*<<< orphan*/  vin_max; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  LTC2978_MFR_TEMPERATURE_PEAK ; 
 int /*<<< orphan*/  LTC2978_MFR_VIN_PEAK ; 
 int /*<<< orphan*/  LTC2978_MFR_VOUT_PEAK ; 
#define  PMBUS_VIRT_READ_TEMP_MAX 133 
#define  PMBUS_VIRT_READ_VIN_MAX 132 
#define  PMBUS_VIRT_READ_VOUT_MAX 131 
#define  PMBUS_VIRT_RESET_TEMP_HISTORY 130 
#define  PMBUS_VIRT_RESET_VIN_HISTORY 129 
#define  PMBUS_VIRT_RESET_VOUT_HISTORY 128 
 int ltc_get_max (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ltc_read_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int ltc_wait_ready (struct i2c_client*) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 struct ltc2978_data* to_ltc2978_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int ltc2978_read_word_data_common(struct i2c_client *client, int page,
					 int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_VIN_MAX:
		ret = ltc_get_max(data, client, page, LTC2978_MFR_VIN_PEAK,
				  &data->vin_max);
		break;
	case PMBUS_VIRT_READ_VOUT_MAX:
		ret = ltc_read_word_data(client, page, LTC2978_MFR_VOUT_PEAK);
		if (ret >= 0) {
			/*
			 * VOUT is 16 bit unsigned with fixed exponent,
			 * so we can compare it directly
			 */
			if (ret > data->vout_max[page])
				data->vout_max[page] = ret;
			ret = data->vout_max[page];
		}
		break;
	case PMBUS_VIRT_READ_TEMP_MAX:
		ret = ltc_get_max(data, client, page,
				  LTC2978_MFR_TEMPERATURE_PEAK,
				  &data->temp_max[page]);
		break;
	case PMBUS_VIRT_RESET_VOUT_HISTORY:
	case PMBUS_VIRT_RESET_VIN_HISTORY:
	case PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = 0;
		break;
	default:
		ret = ltc_wait_ready(client);
		if (ret < 0)
			return ret;
		ret = -ENODATA;
		break;
	}
	return ret;
}