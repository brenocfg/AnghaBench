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
union hdmi_infoframe {int /*<<< orphan*/  vendor; int /*<<< orphan*/  audio; int /*<<< orphan*/  spd; int /*<<< orphan*/  drm; int /*<<< orphan*/  avi; } ;
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
 size_t HDMI_INFOFRAME_HEADER_SIZE ; 
#define  HDMI_INFOFRAME_TYPE_AUDIO 132 
#define  HDMI_INFOFRAME_TYPE_AVI 131 
#define  HDMI_INFOFRAME_TYPE_DRM 130 
#define  HDMI_INFOFRAME_TYPE_SPD 129 
#define  HDMI_INFOFRAME_TYPE_VENDOR 128 
 int hdmi_audio_infoframe_unpack (int /*<<< orphan*/ *,void const*,size_t) ; 
 int hdmi_avi_infoframe_unpack (int /*<<< orphan*/ *,void const*,size_t) ; 
 int hdmi_drm_infoframe_unpack (int /*<<< orphan*/ *,void const*,size_t) ; 
 int hdmi_spd_infoframe_unpack (int /*<<< orphan*/ *,void const*,size_t) ; 
 int hdmi_vendor_any_infoframe_unpack (int /*<<< orphan*/ *,void const*,size_t) ; 

int hdmi_infoframe_unpack(union hdmi_infoframe *frame,
			  const void *buffer, size_t size)
{
	int ret;
	const u8 *ptr = buffer;

	if (size < HDMI_INFOFRAME_HEADER_SIZE)
		return -EINVAL;

	switch (ptr[0]) {
	case HDMI_INFOFRAME_TYPE_AVI:
		ret = hdmi_avi_infoframe_unpack(&frame->avi, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_DRM:
		ret = hdmi_drm_infoframe_unpack(&frame->drm, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_SPD:
		ret = hdmi_spd_infoframe_unpack(&frame->spd, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_AUDIO:
		ret = hdmi_audio_infoframe_unpack(&frame->audio, buffer, size);
		break;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		ret = hdmi_vendor_any_infoframe_unpack(&frame->vendor, buffer, size);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}