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
struct dpu_media_color_map {scalar_t__ format; int color; int /*<<< orphan*/  const member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ pixel_format; } ;
struct dpu_format {TYPE_1__ base; scalar_t__ unpack_tight; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpu_media_color_map const*) ; 
 int COLOR_FMT_NV12_BPP10_UBWC ; 
 int COLOR_FMT_NV12_UBWC ; 
 int COLOR_FMT_P010_UBWC ; 
#define  COLOR_FMT_RGB565_UBWC 135 
#define  COLOR_FMT_RGBA1010102_UBWC 134 
#define  COLOR_FMT_RGBA8888_UBWC 133 
 scalar_t__ DPU_FORMAT_IS_DX (struct dpu_format const*) ; 
#define  DRM_FORMAT_ABGR2101010 132 
#define  DRM_FORMAT_ABGR8888 131 
#define  DRM_FORMAT_BGR565 130 
 scalar_t__ DRM_FORMAT_NV12 ; 
#define  DRM_FORMAT_XBGR2101010 129 
#define  DRM_FORMAT_XBGR8888 128 

__attribute__((used)) static int _dpu_format_get_media_color_ubwc(const struct dpu_format *fmt)
{
	static const struct dpu_media_color_map dpu_media_ubwc_map[] = {
		{DRM_FORMAT_ABGR8888, COLOR_FMT_RGBA8888_UBWC},
		{DRM_FORMAT_XBGR8888, COLOR_FMT_RGBA8888_UBWC},
		{DRM_FORMAT_ABGR2101010, COLOR_FMT_RGBA1010102_UBWC},
		{DRM_FORMAT_XBGR2101010, COLOR_FMT_RGBA1010102_UBWC},
		{DRM_FORMAT_BGR565, COLOR_FMT_RGB565_UBWC},
	};
	int color_fmt = -1;
	int i;

	if (fmt->base.pixel_format == DRM_FORMAT_NV12) {
		if (DPU_FORMAT_IS_DX(fmt)) {
			if (fmt->unpack_tight)
				color_fmt = COLOR_FMT_NV12_BPP10_UBWC;
			else
				color_fmt = COLOR_FMT_P010_UBWC;
		} else
			color_fmt = COLOR_FMT_NV12_UBWC;
		return color_fmt;
	}

	for (i = 0; i < ARRAY_SIZE(dpu_media_ubwc_map); ++i)
		if (fmt->base.pixel_format == dpu_media_ubwc_map[i].format) {
			color_fmt = dpu_media_ubwc_map[i].color;
			break;
		}
	return color_fmt;
}