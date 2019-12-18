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
struct zl6100_data {int /*<<< orphan*/  access; } ;
struct pmbus_driver_info {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int) ; 
 int ENXIO ; 
 int MFR_VMON_OV_FAULT_LIMIT ; 
 int MFR_VMON_UV_FAULT_LIMIT ; 
 int PMBUS_VIRT_BASE ; 
#define  PMBUS_VIRT_VMON_OV_FAULT_LIMIT 131 
#define  PMBUS_VIRT_VMON_OV_WARN_LIMIT 130 
#define  PMBUS_VIRT_VMON_UV_FAULT_LIMIT 129 
#define  PMBUS_VIRT_VMON_UV_WARN_LIMIT 128 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  pmbus_clear_cache (struct i2c_client*) ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 int pmbus_write_word_data (struct i2c_client*,int,int,int /*<<< orphan*/ ) ; 
 struct zl6100_data* to_zl6100_data (struct pmbus_driver_info const*) ; 
 int /*<<< orphan*/  zl6100_d2l (int /*<<< orphan*/ ) ; 
 int zl6100_l2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zl6100_wait (struct zl6100_data*) ; 

__attribute__((used)) static int zl6100_write_word_data(struct i2c_client *client, int page, int reg,
				  u16 word)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct zl6100_data *data = to_zl6100_data(info);
	int ret, vreg;

	if (page > 0)
		return -ENXIO;

	switch (reg) {
	case PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		word = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(word) * 10, 9));
		vreg = MFR_VMON_OV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		break;
	case PMBUS_VIRT_VMON_OV_FAULT_LIMIT:
		vreg = MFR_VMON_OV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		break;
	case PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		word = zl6100_d2l(DIV_ROUND_CLOSEST(zl6100_l2d(word) * 10, 11));
		vreg = MFR_VMON_UV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		break;
	case PMBUS_VIRT_VMON_UV_FAULT_LIMIT:
		vreg = MFR_VMON_UV_FAULT_LIMIT;
		pmbus_clear_cache(client);
		break;
	default:
		if (reg >= PMBUS_VIRT_BASE)
			return -ENXIO;
		vreg = reg;
	}

	zl6100_wait(data);
	ret = pmbus_write_word_data(client, page, vreg, word);
	data->access = ktime_get();

	return ret;
}