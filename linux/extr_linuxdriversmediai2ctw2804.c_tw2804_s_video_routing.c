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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct tw2804 {int channel; int input; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  channel_registers ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  global_registers ; 
 int read_reg (struct i2c_client*,int,int) ; 
 struct tw2804* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int write_reg (struct i2c_client*,int,int,int) ; 
 scalar_t__ write_regs (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tw2804_s_video_routing(struct v4l2_subdev *sd, u32 input, u32 output,
	u32 config)
{
	struct tw2804 *dec = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int reg;

	if (config && config - 1 != dec->channel) {
		if (config > 4) {
			dev_err(&client->dev,
				"channel %d is not between 1 and 4!\n", config);
			return -EINVAL;
		}
		dec->channel = config - 1;
		dev_dbg(&client->dev, "initializing TW2804 channel %d\n",
			dec->channel);
		if (dec->channel == 0 &&
				write_regs(client, global_registers, 0) < 0) {
			dev_err(&client->dev,
				"error initializing TW2804 global registers\n");
			return -EIO;
		}
		if (write_regs(client, channel_registers, dec->channel) < 0) {
			dev_err(&client->dev,
				"error initializing TW2804 channel %d\n",
				dec->channel);
			return -EIO;
		}
	}

	if (input > 1)
		return -EINVAL;

	if (input == dec->input)
		return 0;

	reg = read_reg(client, 0x22, dec->channel);

	if (reg >= 0) {
		if (input == 0)
			reg &= ~(1 << 2);
		else
			reg |= 1 << 2;
		reg = write_reg(client, 0x22, reg, dec->channel);
	}

	if (reg >= 0)
		dec->input = input;
	else
		return reg;
	return 0;
}