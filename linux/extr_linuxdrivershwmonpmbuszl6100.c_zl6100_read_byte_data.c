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
struct zl6100_data {int /*<<< orphan*/  access; } ;
struct pmbus_driver_info {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int PB_VOLTAGE_OV_FAULT ; 
 int PB_VOLTAGE_OV_WARNING ; 
 int PB_VOLTAGE_UV_FAULT ; 
 int PB_VOLTAGE_UV_WARNING ; 
 int PMBUS_STATUS_MFR_SPECIFIC ; 
#define  PMBUS_VIRT_STATUS_VMON 128 
 int VMON_OV_FAULT ; 
 int VMON_OV_WARNING ; 
 int VMON_UV_FAULT ; 
 int VMON_UV_WARNING ; 
 int /*<<< orphan*/  ktime_get () ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 int pmbus_read_byte_data (struct i2c_client*,int,int) ; 
 struct zl6100_data* to_zl6100_data (struct pmbus_driver_info const*) ; 
 int /*<<< orphan*/  zl6100_wait (struct zl6100_data*) ; 

__attribute__((used)) static int zl6100_read_byte_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct zl6100_data *data = to_zl6100_data(info);
	int ret, status;

	if (page > 0)
		return -ENXIO;

	zl6100_wait(data);

	switch (reg) {
	case PMBUS_VIRT_STATUS_VMON:
		ret = pmbus_read_byte_data(client, 0,
					   PMBUS_STATUS_MFR_SPECIFIC);
		if (ret < 0)
			break;

		status = 0;
		if (ret & VMON_UV_WARNING)
			status |= PB_VOLTAGE_UV_WARNING;
		if (ret & VMON_OV_WARNING)
			status |= PB_VOLTAGE_OV_WARNING;
		if (ret & VMON_UV_FAULT)
			status |= PB_VOLTAGE_UV_FAULT;
		if (ret & VMON_OV_FAULT)
			status |= PB_VOLTAGE_OV_FAULT;
		ret = status;
		break;
	default:
		ret = pmbus_read_byte_data(client, page, reg);
		break;
	}
	data->access = ktime_get();

	return ret;
}