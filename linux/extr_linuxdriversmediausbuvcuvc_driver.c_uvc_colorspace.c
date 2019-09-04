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
typedef  size_t u8 ;
typedef  size_t const u32 ;

/* Variables and functions */
 size_t const ARRAY_SIZE (size_t const*) ; 
#define  V4L2_COLORSPACE_470_SYSTEM_BG 132 
#define  V4L2_COLORSPACE_470_SYSTEM_M 131 
#define  V4L2_COLORSPACE_SMPTE170M 130 
#define  V4L2_COLORSPACE_SMPTE240M 129 
#define  V4L2_COLORSPACE_SRGB 128 

__attribute__((used)) static u32 uvc_colorspace(const u8 primaries)
{
	static const u8 colorprimaries[] = {
		0,
		V4L2_COLORSPACE_SRGB,
		V4L2_COLORSPACE_470_SYSTEM_M,
		V4L2_COLORSPACE_470_SYSTEM_BG,
		V4L2_COLORSPACE_SMPTE170M,
		V4L2_COLORSPACE_SMPTE240M,
	};

	if (primaries < ARRAY_SIZE(colorprimaries))
		return colorprimaries[primaries];

	return 0;
}