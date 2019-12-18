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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int clk_lane_reg1; } ;
struct mipid02_dev {TYPE_1__ r; struct v4l2_subdev* s_subdev; struct i2c_client* i2c_client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mipid02_get_link_freq_from_cid_link_freq (struct mipid02_dev*,struct v4l2_subdev*) ; 
 int mipid02_get_link_freq_from_cid_pixel_rate (struct mipid02_dev*,struct v4l2_subdev*) ; 

__attribute__((used)) static int mipid02_configure_from_rx_speed(struct mipid02_dev *bridge)
{
	struct i2c_client *client = bridge->i2c_client;
	struct v4l2_subdev *subdev = bridge->s_subdev;
	u32 link_freq;

	link_freq = mipid02_get_link_freq_from_cid_link_freq(bridge, subdev);
	if (!link_freq) {
		link_freq = mipid02_get_link_freq_from_cid_pixel_rate(bridge,
								      subdev);
		if (!link_freq) {
			dev_err(&client->dev, "Failed to get link frequency");
			return -EINVAL;
		}
	}

	dev_dbg(&client->dev, "detect link_freq = %d Hz", link_freq);
	bridge->r.clk_lane_reg1 |= (2000000000 / link_freq) << 2;

	return 0;
}