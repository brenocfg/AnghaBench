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
struct pmbus_samples_attr {int /*<<< orphan*/  reg; } ;
struct pmbus_driver_info {int* func; } ;
struct pmbus_data {struct pmbus_driver_info* info; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pmbus_samples_attr*) ; 
 int PMBUS_HAVE_SAMPLES ; 
 int pmbus_add_samples_attr (struct pmbus_data*,int /*<<< orphan*/ ,struct pmbus_samples_attr*) ; 
 int /*<<< orphan*/  pmbus_check_word_register (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmbus_samples_attr* pmbus_samples_registers ; 

__attribute__((used)) static int pmbus_add_samples_attributes(struct i2c_client *client,
					struct pmbus_data *data)
{
	const struct pmbus_driver_info *info = data->info;
	int s;

	if (!(info->func[0] & PMBUS_HAVE_SAMPLES))
		return 0;

	for (s = 0; s < ARRAY_SIZE(pmbus_samples_registers); s++) {
		struct pmbus_samples_attr *attr;
		int ret;

		attr = &pmbus_samples_registers[s];
		if (!pmbus_check_word_register(client, 0, attr->reg))
			continue;

		ret = pmbus_add_samples_attr(data, 0, attr);
		if (ret)
			return ret;
	}

	return 0;
}