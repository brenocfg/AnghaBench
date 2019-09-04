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
typedef  enum dcn_bw_defs { ____Placeholder_dcn_bw_defs } dcn_bw_defs ;

/* Variables and functions */
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 141 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 140 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 128 
 int dcn_bw_rgb_sub_16 ; 
 int dcn_bw_rgb_sub_32 ; 
 int dcn_bw_rgb_sub_64 ; 
 int dcn_bw_yuv420_sub_10 ; 
 int dcn_bw_yuv420_sub_8 ; 

__attribute__((used)) static enum dcn_bw_defs tl_pixel_format_to_bw_defs(enum surface_pixel_format format)
{
	switch (format) {
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		return dcn_bw_rgb_sub_16;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		return dcn_bw_rgb_sub_32;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		return dcn_bw_rgb_sub_64;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		return dcn_bw_yuv420_sub_8;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		return dcn_bw_yuv420_sub_10;
	default:
		return dcn_bw_rgb_sub_32;
	}
}