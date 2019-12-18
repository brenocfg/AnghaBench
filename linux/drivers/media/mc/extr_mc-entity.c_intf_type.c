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
struct media_interface {int type; } ;

/* Variables and functions */
#define  MEDIA_INTF_T_DVB_CA 138 
#define  MEDIA_INTF_T_DVB_DEMUX 137 
#define  MEDIA_INTF_T_DVB_DVR 136 
#define  MEDIA_INTF_T_DVB_FE 135 
#define  MEDIA_INTF_T_DVB_NET 134 
#define  MEDIA_INTF_T_V4L_RADIO 133 
#define  MEDIA_INTF_T_V4L_SUBDEV 132 
#define  MEDIA_INTF_T_V4L_SWRADIO 131 
#define  MEDIA_INTF_T_V4L_TOUCH 130 
#define  MEDIA_INTF_T_V4L_VBI 129 
#define  MEDIA_INTF_T_V4L_VIDEO 128 

__attribute__((used)) static inline const char *intf_type(struct media_interface *intf)
{
	switch (intf->type) {
	case MEDIA_INTF_T_DVB_FE:
		return "dvb-frontend";
	case MEDIA_INTF_T_DVB_DEMUX:
		return "dvb-demux";
	case MEDIA_INTF_T_DVB_DVR:
		return "dvb-dvr";
	case MEDIA_INTF_T_DVB_CA:
		return  "dvb-ca";
	case MEDIA_INTF_T_DVB_NET:
		return "dvb-net";
	case MEDIA_INTF_T_V4L_VIDEO:
		return "v4l-video";
	case MEDIA_INTF_T_V4L_VBI:
		return "v4l-vbi";
	case MEDIA_INTF_T_V4L_RADIO:
		return "v4l-radio";
	case MEDIA_INTF_T_V4L_SUBDEV:
		return "v4l-subdev";
	case MEDIA_INTF_T_V4L_SWRADIO:
		return "v4l-swradio";
	case MEDIA_INTF_T_V4L_TOUCH:
		return "v4l-touch";
	default:
		return "unknown-intf";
	}
}