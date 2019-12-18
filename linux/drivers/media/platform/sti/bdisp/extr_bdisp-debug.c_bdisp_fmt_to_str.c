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
struct bdisp_frame {int /*<<< orphan*/  field; TYPE_1__* fmt; } ;
struct TYPE_2__ {int pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
#define  V4L2_PIX_FMT_ABGR32 133 
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB565 130 
#define  V4L2_PIX_FMT_XBGR32 129 
#define  V4L2_PIX_FMT_YUV420 128 

__attribute__((used)) static const char *bdisp_fmt_to_str(struct bdisp_frame frame)
{
	switch (frame.fmt->pixelformat) {
	case V4L2_PIX_FMT_YUV420:
		return "YUV420P";
	case V4L2_PIX_FMT_NV12:
		if (frame.field == V4L2_FIELD_INTERLACED)
			return "NV12 interlaced";
		else
			return "NV12";
	case V4L2_PIX_FMT_RGB565:
		return "RGB16";
	case V4L2_PIX_FMT_RGB24:
		return "RGB24";
	case V4L2_PIX_FMT_XBGR32:
		return "XRGB";
	case V4L2_PIX_FMT_ABGR32:
		return "ARGB";
	default:
		return "????";
	}
}