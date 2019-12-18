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
#define  V4L2_COLORSPACE_REC709 131 
#define  V4L2_COLORSPACE_SMPTE170M 130 
#define  V4L2_COLORSPACE_SMPTE240M 129 
#define  V4L2_COLORSPACE_SRGB 128 

__attribute__((used)) static u32 v4l2_colorspace_to_mcu_colorspace(enum v4l2_colorspace colorspace)
{
	switch (colorspace) {
	case V4L2_COLORSPACE_REC709:
		return 2;
	case V4L2_COLORSPACE_SMPTE170M:
		return 3;
	case V4L2_COLORSPACE_SMPTE240M:
		return 4;
	case V4L2_COLORSPACE_SRGB:
		return 7;
	default:
		/* UNKNOWN */
		return 0;
	}
}