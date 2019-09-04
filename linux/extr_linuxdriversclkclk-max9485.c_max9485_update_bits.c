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
struct max9485_driver_data {int /*<<< orphan*/  reg_value; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_master_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int max9485_update_bits(struct max9485_driver_data *drvdata,
			       u8 mask, u8 value)
{
	int ret;

	drvdata->reg_value &= ~mask;
	drvdata->reg_value |= value;

	dev_dbg(&drvdata->client->dev,
		"updating mask 0x%02x value 0x%02x -> 0x%02x\n",
		mask, value, drvdata->reg_value);

	ret = i2c_master_send(drvdata->client,
			      &drvdata->reg_value,
			      sizeof(drvdata->reg_value));

	return ret < 0 ? ret : 0;
}