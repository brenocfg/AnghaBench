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
struct zl6100_data {scalar_t__ id; int /*<<< orphan*/  access; } ;
struct pmbus_driver_info {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int) ; 
 int ENXIO ; 
 int MFR_READ_VMON ; 
 int MFR_VMON_OV_FAULT_LIMIT ; 
 int MFR_VMON_UV_FAULT_LIMIT ; 
#define  PMBUS_IOUT_OC_WARN_LIMIT 135 
 int PMBUS_VIRT_BASE ; 
#define  PMBUS_VIRT_READ_VMON 134 
#define  PMBUS_VIRT_VMON_OV_FAULT_LIMIT 133 
#define  PMBUS_VIRT_VMON_OV_WARN_LIMIT 132 
#define  PMBUS_VIRT_VMON_UV_FAULT_LIMIT 131 
#define  PMBUS_VIRT_VMON_UV_WARN_LIMIT 130 
#define  PMBUS_VOUT_OV_WARN_LIMIT 129 
#define  PMBUS_VOUT_UV_WARN_LIMIT 128 
 int /*<<< orphan*/  ktime_get () ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 int pmbus_read_word_data (struct i2c_client*,int,int) ; 
 struct zl6100_data* to_zl6100_data (struct pmbus_driver_info const*) ; 
 scalar_t__ zl2005 ; 
 int zl6100_d2l (int /*<<< orphan*/ ) ; 
 int zl6100_l2d (int) ; 
 int /*<<< orphan*/  zl6100_wait (struct zl6100_data*) ; 

__attribute__((used)) static int zl6100_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct zl6100_data *data = to_zl6100_data(info);
	int ret, vreg;

	if (page > 0)
		return -ENXIO;

	if (data->id == zl2005) {
		/*
		 * Limit register detection is not reliable on ZL2005.
		 * Make sure registers are not erroneously detected.
		 */
		switch (reg) {
		case PMBUS_VOUT_OV_WARN_LIMIT:
		case PMBUS_VOUT_UV_WARN_LIMIT:
		case PMBUS_IOUT_OC_WARN_LIMIT:
			return -ENXIO;
		}
	}

	switch (reg) {
	case PMBUS_VIRT_READ_VMON:
		vreg = MFR_READ_VMON;
		break;
	case PMBUS_VIRT_VMON_OV_WARN_LIMIT:
	case PMBUS_VIRT_VMON_OV_FAULT_LIMIT:
		vreg = MFR_VMON_OV_FAULT_LIMIT;
		break;
	case PMBUS_VIRT_VMON_UV_WARN_LIMIT:
	case PMBUS_VIRT_VMON_UV_FAULT_LIMIT:
		vreg = MFR_VMON_UV_FAULT_LIMIT;
		break;
	default:
		if (reg >= PMBUS_VIRT_BASE)
			return -ENXIO;
		vreg = reg;
		break;
	}

	zl6100_wait(data);
	ret = pmbus_read_word_data(client, page, vreg);
	data->access = ktime_get();
	if (ret < 0)
		return ret;

	switch (reg) {
	case PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		ret = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(ret) * 9, 10));
		break;
	case PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		ret = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(ret) * 11, 10));
		break;
	}

	return ret;
}