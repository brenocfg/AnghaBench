#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int error; } ;
struct v4l2_subdev {TYPE_1__* ctrl_handler; } ;
struct wm8739_state {int clock_freq; TYPE_1__ hdl; void* volume; void* balance; void* mute; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_5__* adapter; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  R6 ; 
 int /*<<< orphan*/  R7 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 struct wm8739_state* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_1__*) ; 
 void* v4l2_ctrl_new_std (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8739_ctrl_ops ; 
 int /*<<< orphan*/  wm8739_ops ; 
 int /*<<< orphan*/  wm8739_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8739_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct wm8739_state *state;
	struct v4l2_subdev *sd;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &wm8739_ops);
	v4l2_ctrl_handler_init(&state->hdl, 2);
	state->volume = v4l2_ctrl_new_std(&state->hdl, &wm8739_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, 65535 / 100, 50736);
	state->mute = v4l2_ctrl_new_std(&state->hdl, &wm8739_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	state->balance = v4l2_ctrl_new_std(&state->hdl, &wm8739_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, 65535 / 100, 32768);
	sd->ctrl_handler = &state->hdl;
	if (state->hdl.error) {
		int err = state->hdl.error;

		v4l2_ctrl_handler_free(&state->hdl);
		return err;
	}
	v4l2_ctrl_cluster(3, &state->volume);

	state->clock_freq = 48000;

	/* Initialize wm8739 */

	/* reset */
	wm8739_write(sd, R15, 0x00);
	/* filter setting, high path, offet clear */
	wm8739_write(sd, R5, 0x000);
	/* ADC, OSC, Power Off mode Disable */
	wm8739_write(sd, R6, 0x000);
	/* Digital Audio interface format:
	   Enable Master mode, 24 bit, MSB first/left justified */
	wm8739_write(sd, R7, 0x049);
	/* sampling control: normal, 256fs, 48KHz sampling rate */
	wm8739_write(sd, R8, 0x000);
	/* activate */
	wm8739_write(sd, R9, 0x001);
	/* set volume/mute */
	v4l2_ctrl_handler_setup(&state->hdl);
	return 0;
}