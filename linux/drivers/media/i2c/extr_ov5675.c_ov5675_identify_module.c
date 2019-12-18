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
typedef  scalar_t__ u32 ;
struct ov5675 {int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OV5675_CHIP_ID ; 
 int /*<<< orphan*/  OV5675_REG_CHIP_ID ; 
 int /*<<< orphan*/  OV5675_REG_VALUE_24BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int ov5675_read_reg (struct ov5675*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5675_identify_module(struct ov5675 *ov5675)
{
	struct i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	int ret;
	u32 val;

	ret = ov5675_read_reg(ov5675, OV5675_REG_CHIP_ID,
			      OV5675_REG_VALUE_24BIT, &val);
	if (ret)
		return ret;

	if (val != OV5675_CHIP_ID) {
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			OV5675_CHIP_ID, val);
		return -ENXIO;
	}

	return 0;
}