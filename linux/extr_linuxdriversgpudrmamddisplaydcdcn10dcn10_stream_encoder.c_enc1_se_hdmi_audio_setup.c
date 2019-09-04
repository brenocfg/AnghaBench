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
struct audio_info {int dummy; } ;
struct audio_crtc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enc1_se_audio_setup (struct stream_encoder*,unsigned int,struct audio_info*) ; 
 int /*<<< orphan*/  enc1_se_enable_audio_clock (struct stream_encoder*,int) ; 
 int /*<<< orphan*/  enc1_se_setup_hdmi_audio (struct stream_encoder*,struct audio_crtc_info*) ; 

void enc1_se_hdmi_audio_setup(
	struct stream_encoder *enc,
	unsigned int az_inst,
	struct audio_info *info,
	struct audio_crtc_info *audio_crtc_info)
{
	enc1_se_enable_audio_clock(enc, true);
	enc1_se_setup_hdmi_audio(enc, audio_crtc_info);
	enc1_se_audio_setup(enc, az_inst, info);
}