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
typedef  int /*<<< orphan*/  u8 ;
struct hdmi_audio_infoframe {int dummy; } ;
struct TYPE_2__ {struct hdmi_audio_infoframe infoframe; } ;
struct hdmi_context {TYPE_1__ audio; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO ; 
 int /*<<< orphan*/  HDMI_AUI_CON ; 
 int /*<<< orphan*/  HDMI_AUI_CON_EVERY_VSYNC ; 
 int /*<<< orphan*/  HDMI_AUI_HEADER0 ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int hdmi_audio_infoframe_pack (struct hdmi_audio_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_reg_write_buf (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_reg_writeb (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_audio_infoframe_apply(struct hdmi_context *hdata)
{
	struct hdmi_audio_infoframe *infoframe = &hdata->audio.infoframe;
	u8 buf[HDMI_INFOFRAME_SIZE(AUDIO)];
	int len;

	len = hdmi_audio_infoframe_pack(infoframe, buf, sizeof(buf));
	if (len < 0)
		return len;

	hdmi_reg_writeb(hdata, HDMI_AUI_CON, HDMI_AUI_CON_EVERY_VSYNC);
	hdmi_reg_write_buf(hdata, HDMI_AUI_HEADER0, buf, len);

	return 0;
}