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
typedef  int u32 ;
struct uvc_frame {int wWidth; } ;
struct uvc_format {int fcc; int bpp; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_M420 131 
#define  V4L2_PIX_FMT_NV12 130 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YVU420 128 

__attribute__((used)) static u32 uvc_v4l2_get_bytesperline(const struct uvc_format *format,
	const struct uvc_frame *frame)
{
	switch (format->fcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_YVU420:
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_M420:
		return frame->wWidth;

	default:
		return format->bpp * frame->wWidth / 8;
	}
}