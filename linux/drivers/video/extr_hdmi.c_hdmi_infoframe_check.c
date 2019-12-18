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
struct TYPE_2__ {int type; } ;
union hdmi_infoframe {TYPE_1__ any; int /*<<< orphan*/  vendor; int /*<<< orphan*/  audio; int /*<<< orphan*/  spd; int /*<<< orphan*/  avi; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HDMI_INFOFRAME_TYPE_AUDIO 131 
#define  HDMI_INFOFRAME_TYPE_AVI 130 
#define  HDMI_INFOFRAME_TYPE_SPD 129 
#define  HDMI_INFOFRAME_TYPE_VENDOR 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int hdmi_audio_infoframe_check (int /*<<< orphan*/ *) ; 
 int hdmi_avi_infoframe_check (int /*<<< orphan*/ *) ; 
 int hdmi_spd_infoframe_check (int /*<<< orphan*/ *) ; 
 int hdmi_vendor_any_infoframe_check (int /*<<< orphan*/ *) ; 

int
hdmi_infoframe_check(union hdmi_infoframe *frame)
{
	switch (frame->any.type) {
	case HDMI_INFOFRAME_TYPE_AVI:
		return hdmi_avi_infoframe_check(&frame->avi);
	case HDMI_INFOFRAME_TYPE_SPD:
		return hdmi_spd_infoframe_check(&frame->spd);
	case HDMI_INFOFRAME_TYPE_AUDIO:
		return hdmi_audio_infoframe_check(&frame->audio);
	case HDMI_INFOFRAME_TYPE_VENDOR:
		return hdmi_vendor_any_infoframe_check(&frame->vendor);
	default:
		WARN(1, "Bad infoframe type %d\n", frame->any.type);
		return -EINVAL;
	}
}