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
union hdmi_infoframe {TYPE_1__ any; int /*<<< orphan*/  vendor; int /*<<< orphan*/  audio; int /*<<< orphan*/  spd; int /*<<< orphan*/  drm; int /*<<< orphan*/  avi; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  HDMI_INFOFRAME_TYPE_AUDIO 132 
#define  HDMI_INFOFRAME_TYPE_AVI 131 
#define  HDMI_INFOFRAME_TYPE_DRM 130 
#define  HDMI_INFOFRAME_TYPE_SPD 129 
#define  HDMI_INFOFRAME_TYPE_VENDOR 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  hdmi_audio_infoframe_pack (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  hdmi_avi_infoframe_pack (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  hdmi_drm_infoframe_pack (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  hdmi_spd_infoframe_pack (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  hdmi_vendor_any_infoframe_pack (int /*<<< orphan*/ *,void*,size_t) ; 

ssize_t
hdmi_infoframe_pack(union hdmi_infoframe *frame,
		    void *buffer, size_t size)
{
	ssize_t length;

	switch (frame->any.type) {
	case HDMI_INFOFRAME_TYPE_AVI:
		length = hdmi_avi_infoframe_pack(&frame->avi, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_DRM:
		length = hdmi_drm_infoframe_pack(&frame->drm, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_SPD:
		length = hdmi_spd_infoframe_pack(&frame->spd, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_AUDIO:
		length = hdmi_audio_infoframe_pack(&frame->audio, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		length = hdmi_vendor_any_infoframe_pack(&frame->vendor,
							buffer, size);
		break;
	default:
		WARN(1, "Bad infoframe type %d\n", frame->any.type);
		length = -EINVAL;
	}

	return length;
}