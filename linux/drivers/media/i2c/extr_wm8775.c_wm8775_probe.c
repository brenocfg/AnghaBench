#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int error; } ;
struct v4l2_subdev {TYPE_2__* ctrl_handler; } ;
struct wm8775_state {int input; TYPE_1__* loud; TYPE_2__ hdl; void* bal; void* vol; void* mute; struct v4l2_subdev sd; } ;
struct wm8775_platform_data {int is_nova_s; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {struct wm8775_platform_data* platform_data; } ;
struct i2c_client {int addr; TYPE_6__ dev; TYPE_5__* adapter; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ val; } ;

/* Variables and functions */
 int ALC_EN ; 
 int ALC_HOLD ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  R11 ; 
 int /*<<< orphan*/  R12 ; 
 int /*<<< orphan*/  R13 ; 
 int /*<<< orphan*/  R14 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R16 ; 
 int /*<<< orphan*/  R17 ; 
 int /*<<< orphan*/  R18 ; 
 int /*<<< orphan*/  R19 ; 
 int /*<<< orphan*/  R20 ; 
 int /*<<< orphan*/  R21 ; 
 int /*<<< orphan*/  R23 ; 
 int /*<<< orphan*/  R7 ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_LOUDNESS ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 struct wm8775_state* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 void* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8775_ctrl_ops ; 
 int /*<<< orphan*/  wm8775_ops ; 
 int /*<<< orphan*/  wm8775_set_audio (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  wm8775_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8775_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct wm8775_state *state;
	struct v4l2_subdev *sd;
	int err;
	bool is_nova_s = false;

	if (client->dev.platform_data) {
		struct wm8775_platform_data *data = client->dev.platform_data;
		is_nova_s = data->is_nova_s;
	}

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &wm8775_ops);
	state->input = 2;

	v4l2_ctrl_handler_init(&state->hdl, 4);
	state->mute = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	state->vol = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, (65535+99)/100, 0xCF00); /* 0dB*/
	state->bal = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, (65535+99)/100, 32768);
	state->loud = v4l2_ctrl_new_std(&state->hdl, &wm8775_ctrl_ops,
			V4L2_CID_AUDIO_LOUDNESS, 0, 1, 1, 1);
	sd->ctrl_handler = &state->hdl;
	err = state->hdl.error;
	if (err) {
		v4l2_ctrl_handler_free(&state->hdl);
		return err;
	}

	/* Initialize wm8775 */

	/* RESET */
	wm8775_write(sd, R23, 0x000);
	/* Disable zero cross detect timeout */
	wm8775_write(sd, R7, 0x000);
	/* HPF enable, left justified, 24-bit (Philips) mode */
	wm8775_write(sd, R11, 0x021);
	/* Master mode, clock ratio 256fs */
	wm8775_write(sd, R12, 0x102);
	/* Powered up */
	wm8775_write(sd, R13, 0x000);

	if (!is_nova_s) {
		/* ADC gain +2.5dB, enable zero cross */
		wm8775_write(sd, R14, 0x1d4);
		/* ADC gain +2.5dB, enable zero cross */
		wm8775_write(sd, R15, 0x1d4);
		/* ALC Stereo, ALC target level -1dB FS max gain +8dB */
		wm8775_write(sd, R16, 0x1bf);
		/* Enable gain control, use zero cross detection,
		   ALC hold time 42.6 ms */
		wm8775_write(sd, R17, 0x185);
	} else {
		/* ALC stereo, ALC target level -5dB FS, ALC max gain +8dB */
		wm8775_write(sd, R16, 0x1bb);
		/* Set ALC mode and hold time */
		wm8775_write(sd, R17, (state->loud->val ? ALC_EN : 0) | ALC_HOLD);
	}
	/* ALC gain ramp up delay 34 s, ALC gain ramp down delay 33 ms */
	wm8775_write(sd, R18, 0x0a2);
	/* Enable noise gate, threshold -72dBfs */
	wm8775_write(sd, R19, 0x005);
	if (!is_nova_s) {
		/* Transient window 4ms, lower PGA gain limit -1dB */
		wm8775_write(sd, R20, 0x07a);
		/* LRBOTH = 1, use input 2. */
		wm8775_write(sd, R21, 0x102);
	} else {
		/* Transient window 4ms, ALC min gain -5dB  */
		wm8775_write(sd, R20, 0x0fb);

		wm8775_set_audio(sd, 1);      /* set volume/mute/mux */
	}
	return 0;
}