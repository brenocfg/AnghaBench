#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_11__ {int /*<<< orphan*/  function; } ;
struct v4l2_subdev {TYPE_1__* ctrl_handler; TYPE_5__ entity; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_14__ {struct cx25840_platform_data* platform_data; } ;
struct i2c_client {int addr; TYPE_8__ dev; TYPE_7__* adapter; } ;
struct TYPE_10__ {int error; } ;
struct cx25840_state {int audclk_freq; int vbi_line_offset; int id; int rev; int vbi_regs_offset; int /*<<< orphan*/  pvr150_workaround; TYPE_1__ hdl; void* volume; void* mute; int /*<<< orphan*/  std; int /*<<< orphan*/  audmode; int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; struct i2c_client* c; TYPE_6__* pads; struct v4l2_subdev sd; } ;
struct cx25840_platform_data {int /*<<< orphan*/  pvr150_workaround; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/  sig_type; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_6__*) ; 
#define  CX2310X_AV 137 
#define  CX23885_AV 136 
#define  CX23887_AV 135 
#define  CX23888_AV 134 
#define  CX25836 133 
#define  CX25837 132 
#define  CX25840 131 
 int /*<<< orphan*/  CX25840_AUDIO8 ; 
 int /*<<< orphan*/  CX25840_COMPOSITE7 ; 
 size_t CX25840_PAD_INPUT ; 
 size_t CX25840_PAD_VID_OUT ; 
#define  CX25841 130 
#define  CX25842 129 
#define  CX25843 128 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  MEDIA_ENT_F_ATV_DECODER ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  PAD_SIGNAL_ANALOG ; 
 int /*<<< orphan*/  PAD_SIGNAL_DV ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BASS ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_TREBLE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_STD_NTSC_M ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_LANG1 ; 
 int /*<<< orphan*/  cx25840_audio_ctrl_ops ; 
 int /*<<< orphan*/  cx25840_ctrl_ops ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int /*<<< orphan*/  cx25840_ir_probe (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cx25840_ops ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 struct cx25840_state* devm_kzalloc (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int get_cx2388x_ident (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_cx2583x (struct cx25840_state*) ; 
 int media_entity_pads_init (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_1__*) ; 
 void* v4l2_ctrl_new_std (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,...) ; 

__attribute__((used)) static int cx25840_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct cx25840_state *state;
	struct v4l2_subdev *sd;
	int default_volume;
	u32 id;
	u16 device_id;
#if defined(CONFIG_MEDIA_CONTROLLER)
	int ret;
#endif

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_dbg(1, cx25840_debug, client,
		"detecting cx25840 client on address 0x%x\n",
		client->addr << 1);

	device_id = cx25840_read(client, 0x101) << 8;
	device_id |= cx25840_read(client, 0x100);
	v4l_dbg(1, cx25840_debug, client, "device_id = 0x%04x\n", device_id);

	/*
	 * The high byte of the device ID should be
	 * 0x83 for the cx2583x and 0x84 for the cx2584x
	 */
	if ((device_id & 0xff00) == 0x8300) {
		id = CX25836 + ((device_id >> 4) & 0xf) - 6;
	} else if ((device_id & 0xff00) == 0x8400) {
		id = CX25840 + ((device_id >> 4) & 0xf);
	} else if (device_id == 0x0000) {
		id = get_cx2388x_ident(client);
	} else if ((device_id & 0xfff0) == 0x5A30) {
		/* The CX23100 (0x5A3C = 23100) doesn't have an A/V decoder */
		id = CX2310X_AV;
	} else if ((device_id & 0xff) == (device_id >> 8)) {
		v4l_err(client,
			"likely a confused/unresponsive cx2388[578] A/V decoder found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);
		v4l_err(client,
			"A method to reset it from the cx25840 driver software is not known at this time\n");
		return -ENODEV;
	} else {
		v4l_dbg(1, cx25840_debug, client, "cx25840 not found\n");
		return -ENODEV;
	}

	state = devm_kzalloc(&client->dev, sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &cx25840_ops);
#if defined(CONFIG_MEDIA_CONTROLLER)
	/*
	 * TODO: add media controller support for analog video inputs like
	 * composite, svideo, etc.
	 * A real input pad for this analog demod would be like:
	 *                 ___________
	 * TUNER --------> |         |
	 *		   |         |
	 * SVIDEO .......> | cx25840 |
	 *		   |         |
	 * COMPOSITE1 ...> |_________|
	 *
	 * However, at least for now, there's no much gain on modelling
	 * those extra inputs. So, let's add it only when needed.
	 */
	state->pads[CX25840_PAD_INPUT].flags = MEDIA_PAD_FL_SINK;
	state->pads[CX25840_PAD_INPUT].sig_type = PAD_SIGNAL_ANALOG;
	state->pads[CX25840_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
	state->pads[CX25840_PAD_VID_OUT].sig_type = PAD_SIGNAL_DV;
	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;

	ret = media_entity_pads_init(&sd->entity, ARRAY_SIZE(state->pads),
				     state->pads);
	if (ret < 0) {
		v4l_info(client, "failed to initialize media entity!\n");
		return ret;
	}
#endif

	switch (id) {
	case CX23885_AV:
		v4l_info(client, "cx23885 A/V decoder found @ 0x%x (%s)\n",
			 client->addr << 1, client->adapter->name);
		break;
	case CX23887_AV:
		v4l_info(client, "cx23887 A/V decoder found @ 0x%x (%s)\n",
			 client->addr << 1, client->adapter->name);
		break;
	case CX23888_AV:
		v4l_info(client, "cx23888 A/V decoder found @ 0x%x (%s)\n",
			 client->addr << 1, client->adapter->name);
		break;
	case CX2310X_AV:
		v4l_info(client, "cx%d A/V decoder found @ 0x%x (%s)\n",
			 device_id, client->addr << 1, client->adapter->name);
		break;
	case CX25840:
	case CX25841:
	case CX25842:
	case CX25843:
		/*
		 * Note: revision '(device_id & 0x0f) == 2' was never built.
		 * The marking skips from 0x1 == 22 to 0x3 == 23.
		 */
		v4l_info(client, "cx25%3x-2%x found @ 0x%x (%s)\n",
			 (device_id & 0xfff0) >> 4,
			 (device_id & 0x0f) < 3 ? (device_id & 0x0f) + 1
						: (device_id & 0x0f),
			 client->addr << 1, client->adapter->name);
		break;
	case CX25836:
	case CX25837:
	default:
		v4l_info(client, "cx25%3x-%x found @ 0x%x (%s)\n",
			 (device_id & 0xfff0) >> 4, device_id & 0x0f,
			 client->addr << 1, client->adapter->name);
		break;
	}

	state->c = client;
	state->vid_input = CX25840_COMPOSITE7;
	state->aud_input = CX25840_AUDIO8;
	state->audclk_freq = 48000;
	state->audmode = V4L2_TUNER_MODE_LANG1;
	state->vbi_line_offset = 8;
	state->id = id;
	state->rev = device_id;
	state->vbi_regs_offset = id == CX23888_AV ? 0x500 - 0x424 : 0;
	state->std = V4L2_STD_NTSC_M;
	v4l2_ctrl_handler_init(&state->hdl, 9);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			  V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			  V4L2_CID_HUE, -128, 127, 1, 0);
	if (!is_cx2583x(state)) {
		default_volume = cx25840_read(client, 0x8d4);
		/*
		 * Enforce the legacy PVR-350/MSP3400 to PVR-150/CX25843 volume
		 * scale mapping limits to avoid -ERANGE errors when
		 * initializing the volume control
		 */
		if (default_volume > 228) {
			/* Bottom out at -96 dB, v4l2 vol range 0x2e00-0x2fff */
			default_volume = 228;
			cx25840_write(client, 0x8d4, 228);
		} else if (default_volume < 20) {
			/* Top out at + 8 dB, v4l2 vol range 0xfe00-0xffff */
			default_volume = 20;
			cx25840_write(client, 0x8d4, 20);
		}
		default_volume = (((228 - default_volume) >> 1) + 23) << 9;

		state->volume = v4l2_ctrl_new_std(&state->hdl,
						  &cx25840_audio_ctrl_ops,
						  V4L2_CID_AUDIO_VOLUME,
						  0, 65535, 65535 / 100,
						  default_volume);
		state->mute = v4l2_ctrl_new_std(&state->hdl,
						&cx25840_audio_ctrl_ops,
						V4L2_CID_AUDIO_MUTE,
						0, 1, 1, 0);
		v4l2_ctrl_new_std(&state->hdl, &cx25840_audio_ctrl_ops,
				  V4L2_CID_AUDIO_BALANCE,
				  0, 65535, 65535 / 100, 32768);
		v4l2_ctrl_new_std(&state->hdl, &cx25840_audio_ctrl_ops,
				  V4L2_CID_AUDIO_BASS,
				  0, 65535, 65535 / 100, 32768);
		v4l2_ctrl_new_std(&state->hdl, &cx25840_audio_ctrl_ops,
				  V4L2_CID_AUDIO_TREBLE,
				  0, 65535, 65535 / 100, 32768);
	}
	sd->ctrl_handler = &state->hdl;
	if (state->hdl.error) {
		int err = state->hdl.error;

		v4l2_ctrl_handler_free(&state->hdl);
		return err;
	}
	if (!is_cx2583x(state))
		v4l2_ctrl_cluster(2, &state->volume);
	v4l2_ctrl_handler_setup(&state->hdl);

	if (client->dev.platform_data) {
		struct cx25840_platform_data *pdata = client->dev.platform_data;

		state->pvr150_workaround = pdata->pvr150_workaround;
	}

	cx25840_ir_probe(sd);
	return 0;
}