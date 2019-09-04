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
struct mt9v032 {int sysclk; int hratio; int /*<<< orphan*/  pixel_rate; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt9v032_configure_pixel_rate(struct mt9v032 *mt9v032)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9v032->subdev);
	int ret;

	ret = v4l2_ctrl_s_ctrl_int64(mt9v032->pixel_rate,
				     mt9v032->sysclk / mt9v032->hratio);
	if (ret < 0)
		dev_warn(&client->dev, "failed to set pixel rate (%d)\n", ret);
}