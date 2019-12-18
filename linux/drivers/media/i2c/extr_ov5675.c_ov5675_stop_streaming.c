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
struct ov5675 {int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5675_MODE_STANDBY ; 
 int /*<<< orphan*/  OV5675_REG_MODE_SELECT ; 
 int /*<<< orphan*/  OV5675_REG_VALUE_08BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ov5675_write_reg (struct ov5675*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ov5675_stop_streaming(struct ov5675 *ov5675)
{
	struct i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);

	if (ov5675_write_reg(ov5675, OV5675_REG_MODE_SELECT,
			     OV5675_REG_VALUE_08BIT, OV5675_MODE_STANDBY))
		dev_err(&client->dev, "failed to set stream");
}