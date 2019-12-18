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
struct pmbus_sensor_attr {int gbit; scalar_t__ sfunc; int /*<<< orphan*/  class; int /*<<< orphan*/  reg; scalar_t__ label; } ;
struct pmbus_sensor {int dummy; } ;
struct pmbus_driver_info {int dummy; } ;
struct pmbus_data {scalar_t__ has_status_word; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PB_STATUS_BASE ; 
 int pmbus_add_boolean (struct pmbus_data*,char const*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int pmbus_add_label (struct pmbus_data*,char const*,int,scalar_t__,int) ; 
 int pmbus_add_limit_attrs (struct i2c_client*,struct pmbus_data*,struct pmbus_driver_info const*,char const*,int,int,struct pmbus_sensor*,struct pmbus_sensor_attr const*) ; 
 struct pmbus_sensor* pmbus_add_sensor (struct pmbus_data*,char const*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ pmbus_check_status_register (struct i2c_client*,int) ; 

__attribute__((used)) static int pmbus_add_sensor_attrs_one(struct i2c_client *client,
				      struct pmbus_data *data,
				      const struct pmbus_driver_info *info,
				      const char *name,
				      int index, int page,
				      const struct pmbus_sensor_attr *attr,
				      bool paged)
{
	struct pmbus_sensor *base;
	bool upper = !!(attr->gbit & 0xff00);	/* need to check STATUS_WORD */
	int ret;

	if (attr->label) {
		ret = pmbus_add_label(data, name, index, attr->label,
				      paged ? page + 1 : 0);
		if (ret)
			return ret;
	}
	base = pmbus_add_sensor(data, name, "input", index, page, attr->reg,
				attr->class, true, true, true);
	if (!base)
		return -ENOMEM;
	if (attr->sfunc) {
		ret = pmbus_add_limit_attrs(client, data, info, name,
					    index, page, base, attr);
		if (ret < 0)
			return ret;
		/*
		 * Add generic alarm attribute only if there are no individual
		 * alarm attributes, if there is a global alarm bit, and if
		 * the generic status register (word or byte, depending on
		 * which global bit is set) for this page is accessible.
		 */
		if (!ret && attr->gbit &&
		    (!upper || (upper && data->has_status_word)) &&
		    pmbus_check_status_register(client, page)) {
			ret = pmbus_add_boolean(data, name, "alarm", index,
						NULL, NULL,
						PB_STATUS_BASE + page,
						attr->gbit);
			if (ret)
				return ret;
		}
	}
	return 0;
}