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
struct saa6752hs_mpeg_params {scalar_t__ vi_bitrate_mode; int vi_bitrate; int vi_bitrate_peak; scalar_t__ au_encoding; scalar_t__ au_ac3_bitrate; scalar_t__ au_l2_bitrate; } ;
struct saa6752hs_state {struct saa6752hs_mpeg_params params; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int MPEG_TOTAL_TARGET_BITRATE_MAX ; 
 scalar_t__ V4L2_MPEG_AUDIO_AC3_BITRATE_384K ; 
 scalar_t__ V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 scalar_t__ V4L2_MPEG_AUDIO_L2_BITRATE_384K ; 
 scalar_t__ V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int /*<<< orphan*/  set_reg16 (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  set_reg8 (struct i2c_client*,int,int) ; 

__attribute__((used)) static int saa6752hs_set_bitrate(struct i2c_client *client,
				 struct saa6752hs_state *h)
{
	struct saa6752hs_mpeg_params *params = &h->params;
	int tot_bitrate;
	int is_384k;

	/* set the bitrate mode */
	set_reg8(client, 0x71,
		params->vi_bitrate_mode != V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);

	/* set the video bitrate */
	if (params->vi_bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR) {
		/* set the target bitrate */
		set_reg16(client, 0x80, params->vi_bitrate);

		/* set the max bitrate */
		set_reg16(client, 0x81, params->vi_bitrate_peak);
		tot_bitrate = params->vi_bitrate_peak;
	} else {
		/* set the target bitrate (no max bitrate for CBR) */
		set_reg16(client, 0x81, params->vi_bitrate);
		tot_bitrate = params->vi_bitrate;
	}

	/* set the audio encoding */
	set_reg8(client, 0x93,
			params->au_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3);

	/* set the audio bitrate */
	if (params->au_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3)
		is_384k = V4L2_MPEG_AUDIO_AC3_BITRATE_384K == params->au_ac3_bitrate;
	else
		is_384k = V4L2_MPEG_AUDIO_L2_BITRATE_384K == params->au_l2_bitrate;
	set_reg8(client, 0x94, is_384k);
	tot_bitrate += is_384k ? 384 : 256;

	/* Note: the total max bitrate is determined by adding the video and audio
	   bitrates together and also adding an extra 768kbit/s to stay on the
	   safe side. If more control should be required, then an extra MPEG control
	   should be added. */
	tot_bitrate += 768;
	if (tot_bitrate > MPEG_TOTAL_TARGET_BITRATE_MAX)
		tot_bitrate = MPEG_TOTAL_TARGET_BITRATE_MAX;

	/* set the total bitrate */
	set_reg16(client, 0xb1, tot_bitrate);
	return 0;
}