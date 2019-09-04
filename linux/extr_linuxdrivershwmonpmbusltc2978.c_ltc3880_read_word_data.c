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
struct ltc2978_data {int /*<<< orphan*/  temp2_max; int /*<<< orphan*/ * iout_max; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LTC3880_MFR_IOUT_PEAK ; 
 int /*<<< orphan*/  LTC3880_MFR_TEMPERATURE2_PEAK ; 
#define  PMBUS_VIRT_READ_IOUT_MAX 134 
#define  PMBUS_VIRT_READ_TEMP2_MAX 133 
#define  PMBUS_VIRT_READ_TEMP_MIN 132 
#define  PMBUS_VIRT_READ_VIN_MIN 131 
#define  PMBUS_VIRT_READ_VOUT_MIN 130 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 129 
#define  PMBUS_VIRT_RESET_TEMP2_HISTORY 128 
 int ltc2978_read_word_data_common (struct i2c_client*,int,int) ; 
 int ltc_get_max (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 struct ltc2978_data* to_ltc2978_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int ltc3880_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_IOUT_MAX:
		ret = ltc_get_max(data, client, page, LTC3880_MFR_IOUT_PEAK,
				  &data->iout_max[page]);
		break;
	case PMBUS_VIRT_READ_TEMP2_MAX:
		ret = ltc_get_max(data, client, page,
				  LTC3880_MFR_TEMPERATURE2_PEAK,
				  &data->temp2_max);
		break;
	case PMBUS_VIRT_READ_VIN_MIN:
	case PMBUS_VIRT_READ_VOUT_MIN:
	case PMBUS_VIRT_READ_TEMP_MIN:
		ret = -ENXIO;
		break;
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
	case PMBUS_VIRT_RESET_TEMP2_HISTORY:
		ret = 0;
		break;
	default:
		ret = ltc2978_read_word_data_common(client, page, reg);
		break;
	}
	return ret;
}