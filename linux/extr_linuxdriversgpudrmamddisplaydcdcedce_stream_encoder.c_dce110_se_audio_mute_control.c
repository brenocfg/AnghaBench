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
struct stream_encoder {int dummy; } ;
struct dce110_stream_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_AUDIO_PACKET_CONTROL ; 
 int /*<<< orphan*/  AFMT_AUDIO_SAMPLE_SEND ; 
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dce110_se_audio_mute_control(
	struct stream_encoder *enc,
	bool mute)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);

	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_AUDIO_SAMPLE_SEND, !mute);
}