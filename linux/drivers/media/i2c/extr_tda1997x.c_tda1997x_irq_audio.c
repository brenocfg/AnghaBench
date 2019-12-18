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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {int audio_samplerate; size_t audio_type; int /*<<< orphan*/  client; struct v4l2_subdev sd; } ;

/* Variables and functions */
 void* AUDCFG_TYPE_DST ; 
 void* AUDCFG_TYPE_HBR ; 
 void* AUDCFG_TYPE_OBA ; 
 void* AUDCFG_TYPE_PCM ; 
 int BIT (void*) ; 
 int LAST_STATE_REACHED ; 
 int MASK_AUDIO_FLG ; 
 int MASK_AUDIO_FREQ_FLG ; 
 int MASK_CH_STATE ; 
 int MASK_ERROR_FIFO_PT ; 
 int MASK_MUTE_FLG ; 
 int MASK_SR_FIFO_FIFO_CTRL ; 
 int MASK_SUS_STATUS ; 
 int /*<<< orphan*/  REG_AUDIO_FLAGS ; 
 int /*<<< orphan*/  REG_AUDIO_FREQ ; 
 int /*<<< orphan*/  REG_HDMI_INFO_RST ; 
 int /*<<< orphan*/  REG_INT_FLG_CLR_AUDIO ; 
 int /*<<< orphan*/  REG_SUS_STATUS ; 
 int* audtype_names ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l_info (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void tda1997x_irq_audio(struct tda1997x_state *state, u8 *flags)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	source = io_read(sd, REG_INT_FLG_CLR_AUDIO);
	io_write(sd, REG_INT_FLG_CLR_AUDIO, source);

	/* reset audio FIFO on FIFO pointer error or audio mute */
	if (source & MASK_ERROR_FIFO_PT ||
	    source & MASK_MUTE_FLG) {
		/* audio reset audio FIFO */
		reg = io_read(sd, REG_SUS_STATUS);
		if ((reg & MASK_SUS_STATUS) == LAST_STATE_REACHED) {
			reg = io_read(sd, REG_HDMI_INFO_RST);
			reg |= MASK_SR_FIFO_FIFO_CTRL;
			io_write(sd, REG_HDMI_INFO_RST, reg);
			reg &= ~MASK_SR_FIFO_FIFO_CTRL;
			io_write(sd, REG_HDMI_INFO_RST, reg);
			/* reset channel status IT if present */
			source &= ~(MASK_CH_STATE);
		}
	}
	if (source & MASK_AUDIO_FREQ_FLG) {
		static const int freq[] = {
			0, 32000, 44100, 48000, 88200, 96000, 176400, 192000
		};

		reg = io_read(sd, REG_AUDIO_FREQ);
		state->audio_samplerate = freq[reg & 7];
		v4l_info(state->client, "Audio Frequency Change: %dHz\n",
			 state->audio_samplerate);
	}
	if (source & MASK_AUDIO_FLG) {
		reg = io_read(sd, REG_AUDIO_FLAGS);
		if (reg & BIT(AUDCFG_TYPE_DST))
			state->audio_type = AUDCFG_TYPE_DST;
		if (reg & BIT(AUDCFG_TYPE_OBA))
			state->audio_type = AUDCFG_TYPE_OBA;
		if (reg & BIT(AUDCFG_TYPE_HBR))
			state->audio_type = AUDCFG_TYPE_HBR;
		if (reg & BIT(AUDCFG_TYPE_PCM))
			state->audio_type = AUDCFG_TYPE_PCM;
		v4l_info(state->client, "Audio Type: %s\n",
			 audtype_names[state->audio_type]);
	}
}