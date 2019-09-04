#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,TYPE_1__*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ tsl2550_info ; 

__attribute__((used)) static struct i2c_client *taos_instantiate_device(struct i2c_adapter *adapter)
{
	if (!strncmp(adapter->name, "TAOS TSL2550 EVM", 16)) {
		dev_info(&adapter->dev, "Instantiating device %s at 0x%02x\n",
			tsl2550_info.type, tsl2550_info.addr);
		return i2c_new_device(adapter, &tsl2550_info);
	}

	return NULL;
}