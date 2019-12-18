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
struct pmbus_sensor_attr {int func; } ;
struct pmbus_driver_info {int pages; int* func; } ;
struct pmbus_data {struct pmbus_driver_info* info; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int pmbus_add_sensor_attrs_one (struct i2c_client*,struct pmbus_data*,struct pmbus_driver_info const*,char const*,int,int,struct pmbus_sensor_attr const*,int) ; 
 int pmbus_sensor_is_paged (struct pmbus_driver_info const*,struct pmbus_sensor_attr const*) ; 

__attribute__((used)) static int pmbus_add_sensor_attrs(struct i2c_client *client,
				  struct pmbus_data *data,
				  const char *name,
				  const struct pmbus_sensor_attr *attrs,
				  int nattrs)
{
	const struct pmbus_driver_info *info = data->info;
	int index, i;
	int ret;

	index = 1;
	for (i = 0; i < nattrs; i++) {
		int page, pages;
		bool paged = pmbus_sensor_is_paged(info, attrs);

		pages = paged ? info->pages : 1;
		for (page = 0; page < pages; page++) {
			if (!(info->func[page] & attrs->func))
				continue;
			ret = pmbus_add_sensor_attrs_one(client, data, info,
							 name, index, page,
							 attrs, paged);
			if (ret)
				return ret;
			index++;
		}
		attrs++;
	}
	return 0;
}