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
struct mt9p031 {int /*<<< orphan*/  clk_div; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9P031_OUTPUT_CONTROL_CEN ; 
 int /*<<< orphan*/  MT9P031_PIXEL_CLOCK_CONTROL ; 
 int /*<<< orphan*/  MT9P031_PIXEL_CLOCK_DIVIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT9P031_RST ; 
 int /*<<< orphan*/  MT9P031_RST_DISABLE ; 
 int /*<<< orphan*/  MT9P031_RST_ENABLE ; 
 int mt9p031_set_output_control (struct mt9p031*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt9p031_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9p031_reset(struct mt9p031 *mt9p031)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	int ret;

	/* Disable chip output, synchronous option update */
	ret = mt9p031_write(client, MT9P031_RST, MT9P031_RST_ENABLE);
	if (ret < 0)
		return ret;
	ret = mt9p031_write(client, MT9P031_RST, MT9P031_RST_DISABLE);
	if (ret < 0)
		return ret;

	ret = mt9p031_write(client, MT9P031_PIXEL_CLOCK_CONTROL,
			    MT9P031_PIXEL_CLOCK_DIVIDE(mt9p031->clk_div));
	if (ret < 0)
		return ret;

	return mt9p031_set_output_control(mt9p031, MT9P031_OUTPUT_CONTROL_CEN,
					  0);
}