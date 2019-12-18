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
struct mt9m111 {int /*<<< orphan*/  clk; int /*<<< orphan*/  regulator; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mt9m111_resume (struct mt9m111*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_clk_disable (int /*<<< orphan*/ ) ; 
 int v4l2_clk_enable (int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_power_on(struct mt9m111 *mt9m111)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	int ret;

	ret = v4l2_clk_enable(mt9m111->clk);
	if (ret < 0)
		return ret;

	ret = regulator_enable(mt9m111->regulator);
	if (ret < 0)
		goto out_clk_disable;

	ret = mt9m111_resume(mt9m111);
	if (ret < 0)
		goto out_regulator_disable;

	return 0;

out_regulator_disable:
	regulator_disable(mt9m111->regulator);

out_clk_disable:
	v4l2_clk_disable(mt9m111->clk);

	dev_err(&client->dev, "Failed to resume the sensor: %d\n", ret);

	return ret;
}