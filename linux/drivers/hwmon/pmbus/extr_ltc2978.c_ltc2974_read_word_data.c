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
struct ltc2978_data {int /*<<< orphan*/ * iout_min; int /*<<< orphan*/ * iout_max; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTC2974_MFR_IOUT_MIN ; 
 int /*<<< orphan*/  LTC2974_MFR_IOUT_PEAK ; 
#define  PMBUS_VIRT_READ_IOUT_MAX 130 
#define  PMBUS_VIRT_READ_IOUT_MIN 129 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 128 
 int ltc2978_read_word_data (struct i2c_client*,int,int) ; 
 int ltc_get_max (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ltc_get_min (struct ltc2978_data*,struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 struct ltc2978_data* to_ltc2978_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int ltc2974_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_IOUT_MAX:
		ret = ltc_get_max(data, client, page, LTC2974_MFR_IOUT_PEAK,
				  &data->iout_max[page]);
		break;
	case PMBUS_VIRT_READ_IOUT_MIN:
		ret = ltc_get_min(data, client, page, LTC2974_MFR_IOUT_MIN,
				  &data->iout_min[page]);
		break;
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = 0;
		break;
	default:
		ret = ltc2978_read_word_data(client, page, reg);
		break;
	}
	return ret;
}