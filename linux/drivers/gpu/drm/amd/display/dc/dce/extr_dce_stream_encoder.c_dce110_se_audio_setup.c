#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct stream_encoder {int dummy; } ;
struct dce110_stream_encoder {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ALLSPEAKERS; } ;
struct TYPE_5__ {int /*<<< orphan*/  speaker_flags; TYPE_1__ info; } ;
struct audio_info {TYPE_2__ flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  all; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_AUDIO_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  AFMT_AUDIO_PACKET_CONTROL2 ; 
 int /*<<< orphan*/  AFMT_AUDIO_SRC_CONTROL ; 
 int /*<<< orphan*/  AFMT_AUDIO_SRC_SELECT ; 
 int /*<<< orphan*/  ASSERT (struct audio_info*) ; 
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ speakers_to_channels (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_se_audio_setup(
	struct stream_encoder *enc,
	unsigned int az_inst,
	struct audio_info *audio_info)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);

	uint32_t speakers = 0;
	uint32_t channels = 0;

	ASSERT(audio_info);
	if (audio_info == NULL)
		/* This should not happen.it does so we don't get BSOD*/
		return;

	speakers = audio_info->flags.info.ALLSPEAKERS;
	channels = speakers_to_channels(audio_info->flags.speaker_flags).all;

	/* setup the audio stream source select (audio -> dig mapping) */
	REG_SET(AFMT_AUDIO_SRC_CONTROL, 0, AFMT_AUDIO_SRC_SELECT, az_inst);

	/* Channel allocation */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_CHANNEL_ENABLE, channels);
}