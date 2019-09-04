#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvbios_therm_sensor {int /*<<< orphan*/  offset_constant; } ;
struct nvkm_therm {struct i2c_client* ic; int /*<<< orphan*/  subdev; struct nvbios_therm_sensor bios_sensor; } ;
struct nvkm_i2c_bus {int /*<<< orphan*/  i2c; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct i2c_board_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ (* detect ) (struct i2c_client*,struct i2c_board_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_MODULE_PREFIX ; 
 struct i2c_client* i2c_new_device (int /*<<< orphan*/ *,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct i2c_client*,struct i2c_board_info*) ; 
 TYPE_2__* to_i2c_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
probe_monitoring_device(struct nvkm_i2c_bus *bus,
			struct i2c_board_info *info, void *data)
{
	struct nvkm_therm *therm = data;
	struct nvbios_therm_sensor *sensor = &therm->bios_sensor;
	struct i2c_client *client;

	request_module("%s%s", I2C_MODULE_PREFIX, info->type);

	client = i2c_new_device(&bus->i2c, info);
	if (!client)
		return false;

	if (!client->dev.driver ||
	    to_i2c_driver(client->dev.driver)->detect(client, info)) {
		i2c_unregister_device(client);
		return false;
	}

	nvkm_debug(&therm->subdev,
		   "Found an %s at address 0x%x (controlled by lm_sensors, "
		   "temp offset %+i C)\n",
		   info->type, info->addr, sensor->offset_constant);
	therm->ic = client;
	return true;
}