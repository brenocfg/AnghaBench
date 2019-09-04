#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pmbus_sensor {int dummy; } ;
struct pmbus_data {TYPE_1__* info; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int* func; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PMBUS_HAVE_PWM12 ; 
 int PMBUS_HAVE_PWM34 ; 
 scalar_t__ PMBUS_VIRT_FAN_TARGET_1 ; 
 scalar_t__ PMBUS_VIRT_PWM_1 ; 
 scalar_t__ PMBUS_VIRT_PWM_ENABLE_1 ; 
 int /*<<< orphan*/  PSC_FAN ; 
 int /*<<< orphan*/  PSC_PWM ; 
 struct pmbus_sensor* pmbus_add_sensor (struct pmbus_data*,char*,char*,int,int,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int pmbus_add_fan_ctrl(struct i2c_client *client,
		struct pmbus_data *data, int index, int page, int id,
		u8 config)
{
	struct pmbus_sensor *sensor;

	sensor = pmbus_add_sensor(data, "fan", "target", index, page,
				  PMBUS_VIRT_FAN_TARGET_1 + id, PSC_FAN,
				  false, false, true);

	if (!sensor)
		return -ENOMEM;

	if (!((data->info->func[page] & PMBUS_HAVE_PWM12) ||
			(data->info->func[page] & PMBUS_HAVE_PWM34)))
		return 0;

	sensor = pmbus_add_sensor(data, "pwm", NULL, index, page,
				  PMBUS_VIRT_PWM_1 + id, PSC_PWM,
				  false, false, true);

	if (!sensor)
		return -ENOMEM;

	sensor = pmbus_add_sensor(data, "pwm", "enable", index, page,
				  PMBUS_VIRT_PWM_ENABLE_1 + id, PSC_PWM,
				  true, false, false);

	if (!sensor)
		return -ENOMEM;

	return 0;
}