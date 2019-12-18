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
typedef  int /*<<< orphan*/  u16 ;
struct pmbus_driver_info {int dummy; } ;
struct ltc2978_data {int iin_max; int iin_min; int pin_max; int pin_min; int* iout_max; int* iout_min; int temp2_max; int* vout_min; int vin_min; int vin_max; int* temp_min; int* temp_max; int /*<<< orphan*/ * vout_max; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
#define  PMBUS_VIRT_RESET_IIN_HISTORY 134 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 133 
#define  PMBUS_VIRT_RESET_PIN_HISTORY 132 
#define  PMBUS_VIRT_RESET_TEMP2_HISTORY 131 
#define  PMBUS_VIRT_RESET_TEMP_HISTORY 130 
#define  PMBUS_VIRT_RESET_VIN_HISTORY 129 
#define  PMBUS_VIRT_RESET_VOUT_HISTORY 128 
 int ltc2978_clear_peaks (struct ltc2978_data*,struct i2c_client*,int) ; 
 int ltc_wait_ready (struct i2c_client*) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 struct ltc2978_data* to_ltc2978_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int ltc2978_write_word_data(struct i2c_client *client, int page,
				    int reg, u16 word)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_RESET_IIN_HISTORY:
		data->iin_max = 0x7c00;
		data->iin_min = 0x7bff;
		ret = ltc2978_clear_peaks(data, client, 0);
		break;
	case PMBUS_VIRT_RESET_PIN_HISTORY:
		data->pin_max = 0x7c00;
		data->pin_min = 0x7bff;
		ret = ltc2978_clear_peaks(data, client, 0);
		break;
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
		data->iout_max[page] = 0x7c00;
		data->iout_min[page] = 0xfbff;
		ret = ltc2978_clear_peaks(data, client, page);
		break;
	case PMBUS_VIRT_RESET_TEMP2_HISTORY:
		data->temp2_max = 0x7c00;
		ret = ltc2978_clear_peaks(data, client, page);
		break;
	case PMBUS_VIRT_RESET_VOUT_HISTORY:
		data->vout_min[page] = 0xffff;
		data->vout_max[page] = 0;
		ret = ltc2978_clear_peaks(data, client, page);
		break;
	case PMBUS_VIRT_RESET_VIN_HISTORY:
		data->vin_min = 0x7bff;
		data->vin_max = 0x7c00;
		ret = ltc2978_clear_peaks(data, client, page);
		break;
	case PMBUS_VIRT_RESET_TEMP_HISTORY:
		data->temp_min[page] = 0x7bff;
		data->temp_max[page] = 0x7c00;
		ret = ltc2978_clear_peaks(data, client, page);
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