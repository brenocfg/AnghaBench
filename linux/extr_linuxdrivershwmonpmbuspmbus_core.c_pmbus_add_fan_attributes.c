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
struct pmbus_driver_info {int pages; int* func; } ;
struct pmbus_data {struct pmbus_driver_info* info; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int PB_FAN_1_INSTALLED ; 
 int PB_FAN_FAN1_FAULT ; 
 int PB_FAN_FAN1_WARNING ; 
 int PB_STATUS_FAN34_BASE ; 
 int PB_STATUS_FAN_BASE ; 
 int /*<<< orphan*/  PSC_FAN ; 
 int _pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int pmbus_add_boolean (struct pmbus_data*,char*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int pmbus_add_fan_ctrl (struct i2c_client*,struct pmbus_data*,int,int,int,int) ; 
 int /*<<< orphan*/ * pmbus_add_sensor (struct pmbus_data*,char*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ pmbus_check_byte_register (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pmbus_check_word_register (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmbus_fan_command_registers ; 
 int /*<<< orphan*/ * pmbus_fan_config_registers ; 
 int* pmbus_fan_flags ; 
 int /*<<< orphan*/ * pmbus_fan_registers ; 
 int* pmbus_fan_status_flags ; 
 int /*<<< orphan*/ * pmbus_fan_status_registers ; 

__attribute__((used)) static int pmbus_add_fan_attributes(struct i2c_client *client,
				    struct pmbus_data *data)
{
	const struct pmbus_driver_info *info = data->info;
	int index = 1;
	int page;
	int ret;

	for (page = 0; page < info->pages; page++) {
		int f;

		for (f = 0; f < ARRAY_SIZE(pmbus_fan_registers); f++) {
			int regval;

			if (!(info->func[page] & pmbus_fan_flags[f]))
				break;

			if (!pmbus_check_word_register(client, page,
						       pmbus_fan_registers[f]))
				break;

			/*
			 * Skip fan if not installed.
			 * Each fan configuration register covers multiple fans,
			 * so we have to do some magic.
			 */
			regval = _pmbus_read_byte_data(client, page,
				pmbus_fan_config_registers[f]);
			if (regval < 0 ||
			    (!(regval & (PB_FAN_1_INSTALLED >> ((f & 1) * 4)))))
				continue;

			if (pmbus_add_sensor(data, "fan", "input", index,
					     page, pmbus_fan_registers[f],
					     PSC_FAN, true, true, true) == NULL)
				return -ENOMEM;

			/* Fan control */
			if (pmbus_check_word_register(client, page,
					pmbus_fan_command_registers[f])) {
				ret = pmbus_add_fan_ctrl(client, data, index,
							 page, f, regval);
				if (ret < 0)
					return ret;
			}

			/*
			 * Each fan status register covers multiple fans,
			 * so we have to do some magic.
			 */
			if ((info->func[page] & pmbus_fan_status_flags[f]) &&
			    pmbus_check_byte_register(client,
					page, pmbus_fan_status_registers[f])) {
				int base;

				if (f > 1)	/* fan 3, 4 */
					base = PB_STATUS_FAN34_BASE + page;
				else
					base = PB_STATUS_FAN_BASE + page;
				ret = pmbus_add_boolean(data, "fan",
					"alarm", index, NULL, NULL, base,
					PB_FAN_FAN1_WARNING >> (f & 1));
				if (ret)
					return ret;
				ret = pmbus_add_boolean(data, "fan",
					"fault", index, NULL, NULL, base,
					PB_FAN_FAN1_FAULT >> (f & 1));
				if (ret)
					return ret;
			}
			index++;
		}
	}
	return 0;
}