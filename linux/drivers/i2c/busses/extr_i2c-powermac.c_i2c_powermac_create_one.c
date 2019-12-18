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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_client {int dummy; } ;
struct i2c_board_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void i2c_powermac_create_one(struct i2c_adapter *adap,
					      const char *type,
					      u32 addr)
{
	struct i2c_board_info info = {};
	struct i2c_client *newdev;

	strncpy(info.type, type, sizeof(info.type));
	info.addr = addr;
	newdev = i2c_new_device(adap, &info);
	if (!newdev)
		dev_err(&adap->dev,
			"i2c-powermac: Failure to register missing %s\n",
			type);
}