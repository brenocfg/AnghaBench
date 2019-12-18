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
struct i2c_client {int dummy; } ;
struct adm1275_data {int /*<<< orphan*/  have_power_sampling; int /*<<< orphan*/  have_temp_max; int /*<<< orphan*/  have_pin_max; int /*<<< orphan*/  have_pin_min; int /*<<< orphan*/  have_iout_min; int /*<<< orphan*/  have_vout; int /*<<< orphan*/  have_oc_fault; int /*<<< orphan*/  have_uc_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1075_READ_VAUX ; 
 int /*<<< orphan*/  ADM1075_VAUX_OV_WARN_LIMIT ; 
 int /*<<< orphan*/  ADM1075_VAUX_UV_WARN_LIMIT ; 
 int /*<<< orphan*/  ADM1275_IOUT_WARN2_LIMIT ; 
 int /*<<< orphan*/  ADM1275_PEAK_IOUT ; 
 int /*<<< orphan*/  ADM1275_PEAK_VIN ; 
 int /*<<< orphan*/  ADM1275_PEAK_VOUT ; 
 int /*<<< orphan*/  ADM1276_PEAK_PIN ; 
 int /*<<< orphan*/  ADM1278_PEAK_TEMP ; 
 int /*<<< orphan*/  ADM1293_IOUT_MIN ; 
 int /*<<< orphan*/  ADM1293_PIN_MIN ; 
 int BIT (int) ; 
 int ENODATA ; 
 int ENXIO ; 
#define  PMBUS_IOUT_OC_FAULT_LIMIT 147 
#define  PMBUS_IOUT_UC_FAULT_LIMIT 146 
#define  PMBUS_READ_VOUT 145 
#define  PMBUS_VIRT_CURR_SAMPLES 144 
#define  PMBUS_VIRT_IN_SAMPLES 143 
#define  PMBUS_VIRT_POWER_SAMPLES 142 
#define  PMBUS_VIRT_READ_IOUT_MAX 141 
#define  PMBUS_VIRT_READ_IOUT_MIN 140 
#define  PMBUS_VIRT_READ_PIN_MAX 139 
#define  PMBUS_VIRT_READ_PIN_MIN 138 
#define  PMBUS_VIRT_READ_TEMP_MAX 137 
#define  PMBUS_VIRT_READ_VIN_MAX 136 
#define  PMBUS_VIRT_READ_VOUT_MAX 135 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 134 
#define  PMBUS_VIRT_RESET_PIN_HISTORY 133 
#define  PMBUS_VIRT_RESET_TEMP_HISTORY 132 
#define  PMBUS_VIRT_RESET_VIN_HISTORY 131 
#define  PMBUS_VIRT_RESET_VOUT_HISTORY 130 
#define  PMBUS_VOUT_OV_WARN_LIMIT 129 
#define  PMBUS_VOUT_UV_WARN_LIMIT 128 
 int adm1275_read_pmon_config (struct adm1275_data const*,struct i2c_client*,int) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 int pmbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adm1275_data* to_adm1275_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int adm1275_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	const struct adm1275_data *data = to_adm1275_data(info);
	int ret = 0;

	if (page > 0)
		return -ENXIO;

	switch (reg) {
	case PMBUS_IOUT_UC_FAULT_LIMIT:
		if (!data->have_uc_fault)
			return -ENXIO;
		ret = pmbus_read_word_data(client, 0, ADM1275_IOUT_WARN2_LIMIT);
		break;
	case PMBUS_IOUT_OC_FAULT_LIMIT:
		if (!data->have_oc_fault)
			return -ENXIO;
		ret = pmbus_read_word_data(client, 0, ADM1275_IOUT_WARN2_LIMIT);
		break;
	case PMBUS_VOUT_OV_WARN_LIMIT:
		if (data->have_vout)
			return -ENODATA;
		ret = pmbus_read_word_data(client, 0,
					   ADM1075_VAUX_OV_WARN_LIMIT);
		break;
	case PMBUS_VOUT_UV_WARN_LIMIT:
		if (data->have_vout)
			return -ENODATA;
		ret = pmbus_read_word_data(client, 0,
					   ADM1075_VAUX_UV_WARN_LIMIT);
		break;
	case PMBUS_READ_VOUT:
		if (data->have_vout)
			return -ENODATA;
		ret = pmbus_read_word_data(client, 0, ADM1075_READ_VAUX);
		break;
	case PMBUS_VIRT_READ_IOUT_MIN:
		if (!data->have_iout_min)
			return -ENXIO;
		ret = pmbus_read_word_data(client, 0, ADM1293_IOUT_MIN);
		break;
	case PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_read_word_data(client, 0, ADM1275_PEAK_IOUT);
		break;
	case PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_read_word_data(client, 0, ADM1275_PEAK_VOUT);
		break;
	case PMBUS_VIRT_READ_VIN_MAX:
		ret = pmbus_read_word_data(client, 0, ADM1275_PEAK_VIN);
		break;
	case PMBUS_VIRT_READ_PIN_MIN:
		if (!data->have_pin_min)
			return -ENXIO;
		ret = pmbus_read_word_data(client, 0, ADM1293_PIN_MIN);
		break;
	case PMBUS_VIRT_READ_PIN_MAX:
		if (!data->have_pin_max)
			return -ENXIO;
		ret = pmbus_read_word_data(client, 0, ADM1276_PEAK_PIN);
		break;
	case PMBUS_VIRT_READ_TEMP_MAX:
		if (!data->have_temp_max)
			return -ENXIO;
		ret = pmbus_read_word_data(client, 0, ADM1278_PEAK_TEMP);
		break;
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
	case PMBUS_VIRT_RESET_VOUT_HISTORY:
	case PMBUS_VIRT_RESET_VIN_HISTORY:
		break;
	case PMBUS_VIRT_RESET_PIN_HISTORY:
		if (!data->have_pin_max)
			return -ENXIO;
		break;
	case PMBUS_VIRT_RESET_TEMP_HISTORY:
		if (!data->have_temp_max)
			return -ENXIO;
		break;
	case PMBUS_VIRT_POWER_SAMPLES:
		if (!data->have_power_sampling)
			return -ENXIO;
		ret = adm1275_read_pmon_config(data, client, true);
		if (ret < 0)
			break;
		ret = BIT(ret);
		break;
	case PMBUS_VIRT_IN_SAMPLES:
	case PMBUS_VIRT_CURR_SAMPLES:
		ret = adm1275_read_pmon_config(data, client, false);
		if (ret < 0)
			break;
		ret = BIT(ret);
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}