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
struct g762_data {int valid; int /*<<< orphan*/  fan_cmd1; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G762_REG_FAN_CMD1 ; 
 int /*<<< orphan*/  G762_REG_FAN_CMD1_DET_FAN_FAIL ; 
 int /*<<< orphan*/  G762_REG_FAN_CMD1_DET_FAN_OOC ; 
 scalar_t__ IS_ERR (struct g762_data*) ; 
 int PTR_ERR (struct g762_data*) ; 
 struct g762_data* g762_update_client (struct device*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int g762_fan_init(struct device *dev)
{
	struct g762_data *data = g762_update_client(dev);

	if (IS_ERR(data))
		return PTR_ERR(data);

	data->fan_cmd1 |= G762_REG_FAN_CMD1_DET_FAN_FAIL;
	data->fan_cmd1 |= G762_REG_FAN_CMD1_DET_FAN_OOC;
	data->valid = false;

	return i2c_smbus_write_byte_data(data->client, G762_REG_FAN_CMD1,
					 data->fan_cmd1);
}