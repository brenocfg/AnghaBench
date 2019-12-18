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
typedef  int u8 ;
struct v4l2_subdev {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int error; } ;
struct saa6752hs_state {int revision; int has_ac3; scalar_t__ standard; int /*<<< orphan*/  video_bitrate_mode; void* video_bitrate; void* video_bitrate_peak; struct v4l2_ctrl_handler hdl; int /*<<< orphan*/  params; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_1__* adapter; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_AUDIO_AC3_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_AUDIO_ENCODING ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_AUDIO_L2_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_STREAM_PID_AUDIO ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_STREAM_PID_PCR ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_STREAM_PID_PMT ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_STREAM_PID_VIDEO ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_STREAM_TYPE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_ASPECT ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_ENCODING ; 
 int V4L2_MPEG_AUDIO_AC3_BITRATE_256K ; 
 int V4L2_MPEG_AUDIO_AC3_BITRATE_384K ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_AUDIO_ENCODING_LAYER_2 ; 
 int V4L2_MPEG_AUDIO_L2_BITRATE_256K ; 
 int V4L2_MPEG_AUDIO_L2_BITRATE_384K ; 
 int V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_ASPECT_16x9 ; 
 int V4L2_MPEG_VIDEO_ASPECT_4x3 ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 
 struct saa6752hs_state* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  i2c_master_send (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  param_defaults ; 
 int /*<<< orphan*/  saa6752hs_ctrl_ops ; 
 int /*<<< orphan*/  saa6752hs_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,...) ; 

__attribute__((used)) static int saa6752hs_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct saa6752hs_state *h;
	struct v4l2_subdev *sd;
	struct v4l2_ctrl_handler *hdl;
	u8 addr = 0x13;
	u8 data[12];

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	h = devm_kzalloc(&client->dev, sizeof(*h), GFP_KERNEL);
	if (h == NULL)
		return -ENOMEM;
	sd = &h->sd;
	v4l2_i2c_subdev_init(sd, client, &saa6752hs_ops);

	i2c_master_send(client, &addr, 1);
	i2c_master_recv(client, data, sizeof(data));
	h->revision = (data[8] << 8) | data[9];
	h->has_ac3 = 0;
	if (h->revision == 0x0206) {
		h->has_ac3 = 1;
		v4l_info(client, "supports AC-3\n");
	}
	h->params = param_defaults;

	hdl = &h->hdl;
	v4l2_ctrl_handler_init(hdl, 14);
	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_ENCODING,
		h->has_ac3 ? V4L2_MPEG_AUDIO_ENCODING_AC3 :
			V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
		0x0d, V4L2_MPEG_AUDIO_ENCODING_LAYER_2);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_L2_BITRATE,
		V4L2_MPEG_AUDIO_L2_BITRATE_384K,
		~((1 << V4L2_MPEG_AUDIO_L2_BITRATE_256K) |
		  (1 << V4L2_MPEG_AUDIO_L2_BITRATE_384K)),
		V4L2_MPEG_AUDIO_L2_BITRATE_256K);

	if (h->has_ac3)
		v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
			V4L2_CID_MPEG_AUDIO_AC3_BITRATE,
			V4L2_MPEG_AUDIO_AC3_BITRATE_384K,
			~((1 << V4L2_MPEG_AUDIO_AC3_BITRATE_256K) |
			  (1 << V4L2_MPEG_AUDIO_AC3_BITRATE_384K)),
			V4L2_MPEG_AUDIO_AC3_BITRATE_256K);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ,
		V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000,
		~(1 << V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000),
		V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_ENCODING,
		V4L2_MPEG_VIDEO_ENCODING_MPEG_2,
		~(1 << V4L2_MPEG_VIDEO_ENCODING_MPEG_2),
		V4L2_MPEG_VIDEO_ENCODING_MPEG_2);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_ASPECT,
		V4L2_MPEG_VIDEO_ASPECT_16x9, 0x01,
		V4L2_MPEG_VIDEO_ASPECT_4x3);

	h->video_bitrate_peak = v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
		1000000, 27000000, 1000, 8000000);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_TYPE,
		V4L2_MPEG_STREAM_TYPE_MPEG2_TS,
		~(1 << V4L2_MPEG_STREAM_TYPE_MPEG2_TS),
		V4L2_MPEG_STREAM_TYPE_MPEG2_TS);

	h->video_bitrate_mode = v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
		V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
	h->video_bitrate = v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE, 1000000, 27000000, 1000, 6000000);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_PMT, 0, (1 << 14) - 1, 1, 16);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_AUDIO, 0, (1 << 14) - 1, 1, 260);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_VIDEO, 0, (1 << 14) - 1, 1, 256);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_PCR, 0, (1 << 14) - 1, 1, 259);
	sd->ctrl_handler = hdl;
	if (hdl->error) {
		int err = hdl->error;

		v4l2_ctrl_handler_free(hdl);
		return err;
	}
	v4l2_ctrl_cluster(3, &h->video_bitrate_mode);
	v4l2_ctrl_handler_setup(hdl);
	h->standard = 0; /* Assume 625 input lines */
	return 0;
}