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
struct v4l2_subdev {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int error; } ;
struct tw9906 {int /*<<< orphan*/  norm; struct v4l2_ctrl_handler hdl; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 struct tw9906* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_registers ; 
 int /*<<< orphan*/  tw9906_ctrl_ops ; 
 int /*<<< orphan*/  tw9906_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct i2c_client*,char*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ write_regs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw9906_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct tw9906 *dec;
	struct v4l2_subdev *sd;
	struct v4l2_ctrl_handler *hdl;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	dec = devm_kzalloc(&client->dev, sizeof(*dec), GFP_KERNEL);
	if (dec == NULL)
		return -ENOMEM;
	sd = &dec->sd;
	v4l2_i2c_subdev_init(sd, client, &tw9906_ops);
	hdl = &dec->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &tw9906_ctrl_ops,
		V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &tw9906_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 255, 1, 0x60);
	v4l2_ctrl_new_std(hdl, &tw9906_ctrl_ops,
		V4L2_CID_HUE, -128, 127, 1, 0);
	sd->ctrl_handler = hdl;
	if (hdl->error) {
		int err = hdl->error;

		v4l2_ctrl_handler_free(hdl);
		return err;
	}

	/* Initialize tw9906 */
	dec->norm = V4L2_STD_NTSC;

	if (write_regs(sd, initial_registers) < 0) {
		v4l2_err(client, "error initializing TW9906\n");
		return -EINVAL;
	}

	return 0;
}