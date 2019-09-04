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
struct regval_list {int reg_num; int value; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int ov2640_write_array(struct i2c_client *client,
			      const struct regval_list *vals)
{
	int ret;

	while ((vals->reg_num != 0xff) || (vals->value != 0xff)) {
		ret = i2c_smbus_write_byte_data(client,
						vals->reg_num, vals->value);
		dev_vdbg(&client->dev, "array: 0x%02x, 0x%02x",
			 vals->reg_num, vals->value);

		if (ret < 0)
			return ret;
		vals++;
	}
	return 0;
}