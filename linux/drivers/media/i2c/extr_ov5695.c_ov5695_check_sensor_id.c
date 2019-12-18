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
typedef  scalar_t__ u32 ;
struct ov5695 {TYPE_1__* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID ; 
 int /*<<< orphan*/  OV5695_REG_CHIP_ID ; 
 int /*<<< orphan*/  OV5695_REG_VALUE_24BIT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__) ; 
 int ov5695_read_reg (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int ov5695_check_sensor_id(struct ov5695 *ov5695,
				  struct i2c_client *client)
{
	struct device *dev = &ov5695->client->dev;
	u32 id = 0;
	int ret;

	ret = ov5695_read_reg(client, OV5695_REG_CHIP_ID,
			      OV5695_REG_VALUE_24BIT, &id);
	if (id != CHIP_ID) {
		dev_err(dev, "Unexpected sensor id(%06x), ret(%d)\n", id, ret);
		return ret;
	}

	dev_info(dev, "Detected OV%06x sensor\n", CHIP_ID);

	return 0;
}