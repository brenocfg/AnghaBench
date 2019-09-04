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
typedef  enum pixel_fmt { ____Placeholder_pixel_fmt } pixel_fmt ;
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;

/* Variables and functions */
 int IPU_COLORSPACE_RGB ; 
 int IPU_COLORSPACE_YCBCR ; 
#define  IPU_PIX_FMT_BGR24 132 
#define  IPU_PIX_FMT_BGR32 131 
#define  IPU_PIX_FMT_RGB24 130 
#define  IPU_PIX_FMT_RGB32 129 
#define  IPU_PIX_FMT_RGB565 128 

__attribute__((used)) static enum ipu_color_space format_to_colorspace(enum pixel_fmt fmt)
{
	switch (fmt) {
	case IPU_PIX_FMT_RGB565:
	case IPU_PIX_FMT_BGR24:
	case IPU_PIX_FMT_RGB24:
	case IPU_PIX_FMT_BGR32:
	case IPU_PIX_FMT_RGB32:
		return IPU_COLORSPACE_RGB;
	default:
		return IPU_COLORSPACE_YCBCR;
	}
}