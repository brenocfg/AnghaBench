#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_7__* adapter; } ;
struct TYPE_10__ {int error; } ;
struct TYPE_9__ {TYPE_2__* ctrl_handler; } ;
struct adv7343_state {int reg00; int reg01; int reg02; int reg35; TYPE_2__ hdl; TYPE_1__ sd; int /*<<< orphan*/  std; int /*<<< orphan*/  output; int /*<<< orphan*/  reg82; int /*<<< orphan*/  reg80; int /*<<< orphan*/  pdata; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_MAX ; 
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_MIN ; 
 int /*<<< orphan*/  ADV7343_COMPOSITE_ID ; 
 int /*<<< orphan*/  ADV7343_GAIN_DEF ; 
 int /*<<< orphan*/  ADV7343_GAIN_MAX ; 
 int /*<<< orphan*/  ADV7343_GAIN_MIN ; 
 int /*<<< orphan*/  ADV7343_HUE_DEF ; 
 int /*<<< orphan*/  ADV7343_HUE_MAX ; 
 int /*<<< orphan*/  ADV7343_HUE_MIN ; 
 int /*<<< orphan*/  ADV7343_SD_MODE_REG1_DEFAULT ; 
 int /*<<< orphan*/  ADV7343_SD_MODE_REG2_DEFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  adv7343_ctrl_ops ; 
 int /*<<< orphan*/  adv7343_get_pdata (struct i2c_client*) ; 
 int adv7343_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  adv7343_ops ; 
 struct adv7343_state* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7343_probe(struct i2c_client *client)
{
	struct adv7343_state *state;
	int err;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, sizeof(struct adv7343_state),
			     GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	/* Copy board specific information here */
	state->pdata = adv7343_get_pdata(client);

	state->reg00	= 0x80;
	state->reg01	= 0x00;
	state->reg02	= 0x20;
	state->reg35	= 0x00;
	state->reg80	= ADV7343_SD_MODE_REG1_DEFAULT;
	state->reg82	= ADV7343_SD_MODE_REG2_DEFAULT;

	state->output = ADV7343_COMPOSITE_ID;
	state->std = V4L2_STD_NTSC;

	v4l2_i2c_subdev_init(&state->sd, client, &adv7343_ops);

	v4l2_ctrl_handler_init(&state->hdl, 2);
	v4l2_ctrl_new_std(&state->hdl, &adv7343_ctrl_ops,
			V4L2_CID_BRIGHTNESS, ADV7343_BRIGHTNESS_MIN,
					     ADV7343_BRIGHTNESS_MAX, 1,
					     ADV7343_BRIGHTNESS_DEF);
	v4l2_ctrl_new_std(&state->hdl, &adv7343_ctrl_ops,
			V4L2_CID_HUE, ADV7343_HUE_MIN,
				      ADV7343_HUE_MAX, 1,
				      ADV7343_HUE_DEF);
	v4l2_ctrl_new_std(&state->hdl, &adv7343_ctrl_ops,
			V4L2_CID_GAIN, ADV7343_GAIN_MIN,
				       ADV7343_GAIN_MAX, 1,
				       ADV7343_GAIN_DEF);
	state->sd.ctrl_handler = &state->hdl;
	if (state->hdl.error) {
		err = state->hdl.error;
		goto done;
	}
	v4l2_ctrl_handler_setup(&state->hdl);

	err = adv7343_initialize(&state->sd);
	if (err)
		goto done;

	err = v4l2_async_register_subdev(&state->sd);

done:
	if (err < 0)
		v4l2_ctrl_handler_free(&state->hdl);

	return err;
}