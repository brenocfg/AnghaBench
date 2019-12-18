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
struct ltc2978_data {int* vout_max; int* vout_min; int /*<<< orphan*/ * temp_min; int /*<<< orphan*/  vin_min; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LTC2978_MFR_TEMPERATURE_MIN ; 
 int /*<<< orphan*/  LTC2978_MFR_VIN_MIN ; 
 int /*<<< orphan*/  LTC2978_MFR_VOUT_MIN ; 
#define  PMBUS_VIRT_READ_IOUT_MAX 134 
#define  PMBUS_VIRT_READ_TEMP2_MAX 133 
#define  PMBUS_VIRT_READ_TEMP_MIN 132 
#define  PMBUS_VIRT_READ_VIN_MIN 131 
#define  PMBUS_VIRT_READ_VOUT_MIN 130 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 129 
#define  PMBUS_VIRT_RESET_TEMP2_HISTORY 128 
 int ltc2978_read_word_data_common (struct i2c_client*,int,int) ; 
 int ltc_get_min (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ltc_read_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 struct ltc2978_data* to_ltc2978_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int ltc2978_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_VIN_MIN:
		ret = ltc_get_min(data, client, page, LTC2978_MFR_VIN_MIN,
				  &data->vin_min);
		break;
	case PMBUS_VIRT_READ_VOUT_MIN:
		ret = ltc_read_word_data(client, page, LTC2978_MFR_VOUT_MIN);
		if (ret >= 0) {
			/*
			 * VOUT_MIN is known to not be supported on some lots
			 * of LTC2978 revision 1, and will return the maximum
			 * possible voltage if read. If VOUT_MAX is valid and
			 * lower than the reading of VOUT_MIN, use it instead.
			 */
			if (data->vout_max[page] && ret > data->vout_max[page])
				ret = data->vout_max[page];
			if (ret < data->vout_min[page])
				data->vout_min[page] = ret;
			ret = data->vout_min[page];
		}
		break;
	case PMBUS_VIRT_READ_TEMP_MIN:
		ret = ltc_get_min(data, client, page,
				  LTC2978_MFR_TEMPERATURE_MIN,
				  &data->temp_min[page]);
		break;
	case PMBUS_VIRT_READ_IOUT_MAX:
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
	case PMBUS_VIRT_READ_TEMP2_MAX:
	case PMBUS_VIRT_RESET_TEMP2_HISTORY:
		ret = -ENXIO;
		break;
	default:
		ret = ltc2978_read_word_data_common(client, page, reg);
		break;
	}
	return ret;
}