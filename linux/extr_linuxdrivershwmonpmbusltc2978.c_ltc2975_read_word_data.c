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
struct ltc2978_data {int /*<<< orphan*/  pin_min; int /*<<< orphan*/  pin_max; int /*<<< orphan*/  iin_min; int /*<<< orphan*/  iin_max; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTC2975_MFR_IIN_MIN ; 
 int /*<<< orphan*/  LTC2975_MFR_IIN_PEAK ; 
 int /*<<< orphan*/  LTC2975_MFR_PIN_MIN ; 
 int /*<<< orphan*/  LTC2975_MFR_PIN_PEAK ; 
#define  PMBUS_VIRT_READ_IIN_MAX 133 
#define  PMBUS_VIRT_READ_IIN_MIN 132 
#define  PMBUS_VIRT_READ_PIN_MAX 131 
#define  PMBUS_VIRT_READ_PIN_MIN 130 
#define  PMBUS_VIRT_RESET_IIN_HISTORY 129 
#define  PMBUS_VIRT_RESET_PIN_HISTORY 128 
 int ltc2978_read_word_data (struct i2c_client*,int,int) ; 
 int ltc_get_max (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ltc_get_min (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 struct ltc2978_data* to_ltc2978_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int ltc2975_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_IIN_MAX:
		ret = ltc_get_max(data, client, page, LTC2975_MFR_IIN_PEAK,
				  &data->iin_max);
		break;
	case PMBUS_VIRT_READ_IIN_MIN:
		ret = ltc_get_min(data, client, page, LTC2975_MFR_IIN_MIN,
				  &data->iin_min);
		break;
	case PMBUS_VIRT_READ_PIN_MAX:
		ret = ltc_get_max(data, client, page, LTC2975_MFR_PIN_PEAK,
				  &data->pin_max);
		break;
	case PMBUS_VIRT_READ_PIN_MIN:
		ret = ltc_get_min(data, client, page, LTC2975_MFR_PIN_MIN,
				  &data->pin_min);
		break;
	case PMBUS_VIRT_RESET_IIN_HISTORY:
	case PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = 0;
		break;
	default:
		ret = ltc2978_read_word_data(client, page, reg);
		break;
	}
	return ret;
}