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
struct pmbus_sensor {int data; } ;
struct pmbus_data {int dummy; } ;
struct i2c_client {int dummy; } ;
typedef  enum pmbus_fan_mode { ____Placeholder_pmbus_fan_mode } pmbus_fan_mode ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pmbus_sensor*) ; 
 int PMBUS_VIRT_FAN_TARGET_1 ; 
 int PMBUS_VIRT_PWM_1 ; 
 int PTR_ERR (struct pmbus_sensor*) ; 
 struct pmbus_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/ * pmbus_fan_command_registers ; 
 int /*<<< orphan*/ * pmbus_fan_config_registers ; 
 int* pmbus_fan_rpm_mask ; 
 struct pmbus_sensor* pmbus_find_sensor (struct pmbus_data*,int,int) ; 
 int pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int pmbus_read_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int rpm ; 

__attribute__((used)) static int pmbus_get_fan_rate(struct i2c_client *client, int page, int id,
			      enum pmbus_fan_mode mode,
			      bool from_cache)
{
	struct pmbus_data *data = i2c_get_clientdata(client);
	bool want_rpm, have_rpm;
	struct pmbus_sensor *s;
	int config;
	int reg;

	want_rpm = (mode == rpm);

	if (from_cache) {
		reg = want_rpm ? PMBUS_VIRT_FAN_TARGET_1 : PMBUS_VIRT_PWM_1;
		s = pmbus_find_sensor(data, page, reg + id);
		if (IS_ERR(s))
			return PTR_ERR(s);

		return s->data;
	}

	config = pmbus_read_byte_data(client, page,
				      pmbus_fan_config_registers[id]);
	if (config < 0)
		return config;

	have_rpm = !!(config & pmbus_fan_rpm_mask[id]);
	if (want_rpm == have_rpm)
		return pmbus_read_word_data(client, page,
					    pmbus_fan_command_registers[id]);

	/* Can't sensibly map between RPM and PWM, just return zero */
	return 0;
}