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
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum pixel_format { ____Placeholder_pixel_format } pixel_format ;

/* Variables and functions */
 int PIXEL_FORMAT_420BPP10 ; 
 int PIXEL_FORMAT_420BPP8 ; 
 int PIXEL_FORMAT_ARGB2101010 ; 
 int PIXEL_FORMAT_ARGB2101010_XRBIAS ; 
 int PIXEL_FORMAT_ARGB8888 ; 
 int PIXEL_FORMAT_FP16 ; 
 int PIXEL_FORMAT_INDEX8 ; 
 int PIXEL_FORMAT_RGB565 ; 
 int PIXEL_FORMAT_UNKNOWN ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 142 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 141 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS 140 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 128 

__attribute__((used)) static enum pixel_format convert_pixel_format_to_dalsurface(
		enum surface_pixel_format surface_pixel_format)
{
	enum pixel_format dal_pixel_format = PIXEL_FORMAT_UNKNOWN;

	switch (surface_pixel_format) {
	case SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
		dal_pixel_format = PIXEL_FORMAT_INDEX8;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		dal_pixel_format = PIXEL_FORMAT_RGB565;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		dal_pixel_format = PIXEL_FORMAT_RGB565;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
		dal_pixel_format = PIXEL_FORMAT_ARGB8888;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		dal_pixel_format = PIXEL_FORMAT_ARGB8888;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
		dal_pixel_format = PIXEL_FORMAT_ARGB2101010;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		dal_pixel_format = PIXEL_FORMAT_ARGB2101010;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		dal_pixel_format = PIXEL_FORMAT_ARGB2101010_XRBIAS;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
		dal_pixel_format = PIXEL_FORMAT_FP16;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		dal_pixel_format = PIXEL_FORMAT_420BPP8;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		dal_pixel_format = PIXEL_FORMAT_420BPP10;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	default:
		dal_pixel_format = PIXEL_FORMAT_UNKNOWN;
		break;
	}
	return dal_pixel_format;
}