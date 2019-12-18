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
typedef  enum v4l2_colorspace { ____Placeholder_v4l2_colorspace } v4l2_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int V4L2_COLORSPACE_SMPTE170M ; 
 int V4L2_COLORSPACE_SRGB ; 
#define  V4L2_PIX_FMT_BGR666 135 
#define  V4L2_PIX_FMT_NV12 134 
#define  V4L2_PIX_FMT_NV16 133 
#define  V4L2_PIX_FMT_NV24 132 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB332 130 
#define  V4L2_PIX_FMT_RGB444 129 
#define  V4L2_PIX_FMT_RGB565 128 

__attribute__((used)) static enum v4l2_colorspace sh_veu_4cc2cspace(u32 fourcc)
{
	switch (fourcc) {
	default:
		BUG();
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV24:
		return V4L2_COLORSPACE_SMPTE170M;
	case V4L2_PIX_FMT_RGB332:
	case V4L2_PIX_FMT_RGB444:
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_BGR666:
	case V4L2_PIX_FMT_RGB24:
		return V4L2_COLORSPACE_SRGB;
	}
}