#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pixel_repeat; int /*<<< orphan*/  colorspace; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel_allocation; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_frequency; } ;
struct TYPE_5__ {int type; } ;
union hdmi_infoframe {TYPE_3__ avi; TYPE_2__ audio; TYPE_1__ any; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {int audio_samplerate; int audio_samplesize; TYPE_3__ avi_infoframe; int /*<<< orphan*/  audio_ch_alloc; int /*<<< orphan*/  audio_channels; TYPE_4__* client; struct v4l2_subdev sd; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_176400 141 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_192000 140 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_32000 139 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_44100 138 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_48000 137 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_88200 136 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_96000 135 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM 134 
#define  HDMI_AUDIO_SAMPLE_SIZE_16 133 
#define  HDMI_AUDIO_SAMPLE_SIZE_20 132 
#define  HDMI_AUDIO_SAMPLE_SIZE_24 131 
#define  HDMI_AUDIO_SAMPLE_SIZE_STREAM 130 
 int /*<<< orphan*/  HDMI_COLORSPACE_YUV422 ; 
#define  HDMI_INFOFRAME_TYPE_AUDIO 129 
#define  HDMI_INFOFRAME_TYPE_AVI 128 
 int /*<<< orphan*/  KERN_INFO ; 
 int PIX_REPEAT_CHROMA ; 
 int PIX_REPEAT_MASK_REP ; 
 int PIX_REPEAT_MASK_UP_SEL ; 
 int PIX_REPEAT_SHIFT ; 
 int /*<<< orphan*/  REG_PIX_REPEAT ; 
 int /*<<< orphan*/  RESET_AUDIO ; 
 int /*<<< orphan*/  hdmi_infoframe_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union hdmi_infoframe*) ; 
 int hdmi_infoframe_unpack (union hdmi_infoframe*,int*,int) ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int io_readn (struct v4l2_subdev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_rgb_quantization_range (struct tda1997x_state*) ; 
 int /*<<< orphan*/  tda1997x_configure_audout (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda1997x_configure_csc (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tda1997x_hdmi_info_reset (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l_err (TYPE_4__*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
tda1997x_parse_infoframe(struct tda1997x_state *state, u16 addr)
{
	struct v4l2_subdev *sd = &state->sd;
	union hdmi_infoframe frame;
	u8 buffer[40];
	u8 reg;
	int len, err;

	/* read data */
	len = io_readn(sd, addr, sizeof(buffer), buffer);
	err = hdmi_infoframe_unpack(&frame, buffer, sizeof(buffer));
	if (err) {
		v4l_err(state->client,
			"failed parsing %d byte infoframe: 0x%04x/0x%02x\n",
			len, addr, buffer[0]);
		return err;
	}
	hdmi_infoframe_log(KERN_INFO, &state->client->dev, &frame);
	switch (frame.any.type) {
	/* Audio InfoFrame: see HDMI spec 8.2.2 */
	case HDMI_INFOFRAME_TYPE_AUDIO:
		/* sample rate */
		switch (frame.audio.sample_frequency) {
		case HDMI_AUDIO_SAMPLE_FREQUENCY_32000:
			state->audio_samplerate = 32000;
			break;
		case HDMI_AUDIO_SAMPLE_FREQUENCY_44100:
			state->audio_samplerate = 44100;
			break;
		case HDMI_AUDIO_SAMPLE_FREQUENCY_48000:
			state->audio_samplerate = 48000;
			break;
		case HDMI_AUDIO_SAMPLE_FREQUENCY_88200:
			state->audio_samplerate = 88200;
			break;
		case HDMI_AUDIO_SAMPLE_FREQUENCY_96000:
			state->audio_samplerate = 96000;
			break;
		case HDMI_AUDIO_SAMPLE_FREQUENCY_176400:
			state->audio_samplerate = 176400;
			break;
		case HDMI_AUDIO_SAMPLE_FREQUENCY_192000:
			state->audio_samplerate = 192000;
			break;
		default:
		case HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM:
			break;
		}

		/* sample size */
		switch (frame.audio.sample_size) {
		case HDMI_AUDIO_SAMPLE_SIZE_16:
			state->audio_samplesize = 16;
			break;
		case HDMI_AUDIO_SAMPLE_SIZE_20:
			state->audio_samplesize = 20;
			break;
		case HDMI_AUDIO_SAMPLE_SIZE_24:
			state->audio_samplesize = 24;
			break;
		case HDMI_AUDIO_SAMPLE_SIZE_STREAM:
		default:
			break;
		}

		/* Channel Count */
		state->audio_channels = frame.audio.channels;
		if (frame.audio.channel_allocation &&
		    frame.audio.channel_allocation != state->audio_ch_alloc) {
			/* use the channel assignment from the infoframe */
			state->audio_ch_alloc = frame.audio.channel_allocation;
			tda1997x_configure_audout(sd, state->audio_ch_alloc);
			/* reset the audio FIFO */
			tda1997x_hdmi_info_reset(sd, RESET_AUDIO, false);
		}
		break;

	/* Auxiliary Video information (AVI) InfoFrame: see HDMI spec 8.2.1 */
	case HDMI_INFOFRAME_TYPE_AVI:
		state->avi_infoframe = frame.avi;
		set_rgb_quantization_range(state);

		/* configure upsampler: 0=bypass 1=repeatchroma 2=interpolate */
		reg = io_read(sd, REG_PIX_REPEAT);
		reg &= ~PIX_REPEAT_MASK_UP_SEL;
		if (frame.avi.colorspace == HDMI_COLORSPACE_YUV422)
			reg |= (PIX_REPEAT_CHROMA << PIX_REPEAT_SHIFT);
		io_write(sd, REG_PIX_REPEAT, reg);

		/* ConfigurePixelRepeater: repeat n-times each pixel */
		reg = io_read(sd, REG_PIX_REPEAT);
		reg &= ~PIX_REPEAT_MASK_REP;
		reg |= frame.avi.pixel_repeat;
		io_write(sd, REG_PIX_REPEAT, reg);

		/* configure the receiver with the new colorspace */
		tda1997x_configure_csc(sd);
		break;
	default:
		break;
	}
	return 0;
}