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
struct TYPE_2__ {int length; int /*<<< orphan*/  type; } ;
struct mcu_msg_create_channel {int src_mode; int constraint_set_flags; int sps_param; int pps_param; int enc_option; int beta_offset; int tc_offset; int num_slices; int* me_range; int max_tu_size; int min_tu_size; int max_transfo_depth_intra; int max_transfo_depth_inter; int initial_rem_delay; int cpb_size; int framerate; int clk_ratio; int max_bitrate; int initial_qp; int min_qp; int max_qp; int ip_delta; int pb_delta; int golden_delta; int golden_ref_frequency; int rate_control_option; int gop_ctrl_mode; int freq_ird; int gdr_mode; int subframe_latency; int lda_control_mode; int /*<<< orphan*/  gop_length; scalar_t__ freq_lt; scalar_t__ golden_ref; int /*<<< orphan*/  target_bitrate; int /*<<< orphan*/  rate_control_mode; void* min_cu_size; void* max_cu_size; scalar_t__ tier; int /*<<< orphan*/  level; int /*<<< orphan*/  codec; int /*<<< orphan*/  profile; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  user_id; TYPE_1__ header; } ;
struct allegro_dev {int /*<<< orphan*/  mbox_command; } ;
struct allegro_channel {int cpb_size; int bitrate_peak; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  bitrate_mode; int /*<<< orphan*/  level; int /*<<< orphan*/  codec; int /*<<< orphan*/  profile; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  user_id; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int AL_OPT_LF ; 
 int AL_OPT_LF_X_SLICE ; 
 int AL_OPT_LF_X_TILE ; 
 int AL_OPT_RDO_COST_MODE ; 
 int BIT (int) ; 
 int /*<<< orphan*/  MCU_MSG_TYPE_CREATE_CHANNEL ; 
 int SIZE_MACROBLOCK ; 
 int /*<<< orphan*/  allegro_mbox_write (struct allegro_dev*,int /*<<< orphan*/ *,struct mcu_msg_create_channel*,int) ; 
 int /*<<< orphan*/  allegro_mcu_interrupt (struct allegro_dev*) ; 
 void* ilog2 (int) ; 
 int /*<<< orphan*/  memset (struct mcu_msg_create_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_bitrate_mode_to_mcu_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_colorspace_to_mcu_colorspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_level_to_mcu_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_pixelformat_to_mcu_codec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_pixelformat_to_mcu_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_profile_to_mcu_profile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_mcu_send_create_channel(struct allegro_dev *dev,
					   struct allegro_channel *channel)
{
	struct mcu_msg_create_channel msg;

	memset(&msg, 0, sizeof(msg));

	msg.header.type = MCU_MSG_TYPE_CREATE_CHANNEL;
	msg.header.length = sizeof(msg) - sizeof(msg.header);

	msg.user_id = channel->user_id;
	msg.width = channel->width;
	msg.height = channel->height;
	msg.format = v4l2_pixelformat_to_mcu_format(channel->pixelformat);
	msg.colorspace = v4l2_colorspace_to_mcu_colorspace(channel->colorspace);
	msg.src_mode = 0x0;
	msg.profile = v4l2_profile_to_mcu_profile(channel->profile);
	msg.constraint_set_flags = BIT(1);
	msg.codec = v4l2_pixelformat_to_mcu_codec(channel->codec);
	msg.level = v4l2_level_to_mcu_level(channel->level);
	msg.tier = 0;
	msg.sps_param = BIT(20) | 0x4a;
	msg.pps_param = BIT(2);
	msg.enc_option = AL_OPT_RDO_COST_MODE | AL_OPT_LF_X_TILE |
			 AL_OPT_LF_X_SLICE | AL_OPT_LF;
	msg.beta_offset = -1;
	msg.tc_offset = -1;
	msg.num_slices = 1;
	msg.me_range[0] = 8;
	msg.me_range[1] = 8;
	msg.me_range[2] = 16;
	msg.me_range[3] = 16;
	msg.max_cu_size = ilog2(SIZE_MACROBLOCK);
	msg.min_cu_size = ilog2(8);
	msg.max_tu_size = 2;
	msg.min_tu_size = 2;
	msg.max_transfo_depth_intra = 1;
	msg.max_transfo_depth_inter = 1;

	msg.rate_control_mode =
		v4l2_bitrate_mode_to_mcu_mode(channel->bitrate_mode);
	/* Shall be ]0;cpb_size in 90 kHz units]. Use maximum value. */
	msg.initial_rem_delay =
		((channel->cpb_size * 1000) / channel->bitrate_peak) * 90000;
	/* Encoder expects cpb_size in units of a 90 kHz clock. */
	msg.cpb_size =
		((channel->cpb_size * 1000) / channel->bitrate_peak) * 90000;
	msg.framerate = 25;
	msg.clk_ratio = 1000;
	msg.target_bitrate = channel->bitrate;
	msg.max_bitrate = channel->bitrate_peak;
	msg.initial_qp = 25;
	msg.min_qp = 10;
	msg.max_qp = 51;
	msg.ip_delta = -1;
	msg.pb_delta = -1;
	msg.golden_ref = 0;
	msg.golden_delta = 2;
	msg.golden_ref_frequency = 10;
	msg.rate_control_option = 0x00000000;

	msg.gop_ctrl_mode = 0x00000000;
	msg.freq_ird = 0x7fffffff;
	msg.freq_lt = 0;
	msg.gdr_mode = 0x00000000;
	msg.gop_length = channel->gop_size;
	msg.subframe_latency = 0x00000000;
	msg.lda_control_mode = 0x700d0000;

	allegro_mbox_write(dev, &dev->mbox_command, &msg, sizeof(msg));
	allegro_mcu_interrupt(dev);

	return 0;
}