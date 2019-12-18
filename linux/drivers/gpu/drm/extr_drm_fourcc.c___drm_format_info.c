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
typedef  scalar_t__ u32 ;
struct drm_format_info {scalar_t__ format; int depth; int num_planes; int hsub; int vsub; int has_alpha; int is_yuv; int /*<<< orphan*/  cpp; int /*<<< orphan*/  block_h; int /*<<< orphan*/  block_w; int /*<<< orphan*/  char_per_block; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct drm_format_info const*) ; 
#define  DRM_FORMAT_ABGR1555 221 
#define  DRM_FORMAT_ABGR16161616F 220 
#define  DRM_FORMAT_ABGR2101010 219 
#define  DRM_FORMAT_ABGR4444 218 
#define  DRM_FORMAT_ABGR8888 217 
#define  DRM_FORMAT_ARGB1555 216 
#define  DRM_FORMAT_ARGB16161616F 215 
#define  DRM_FORMAT_ARGB2101010 214 
#define  DRM_FORMAT_ARGB4444 213 
#define  DRM_FORMAT_ARGB8888 212 
#define  DRM_FORMAT_AYUV 211 
#define  DRM_FORMAT_BGR233 210 
#define  DRM_FORMAT_BGR565 209 
#define  DRM_FORMAT_BGR565_A8 208 
#define  DRM_FORMAT_BGR888 207 
#define  DRM_FORMAT_BGR888_A8 206 
#define  DRM_FORMAT_BGRA1010102 205 
#define  DRM_FORMAT_BGRA4444 204 
#define  DRM_FORMAT_BGRA5551 203 
#define  DRM_FORMAT_BGRA8888 202 
#define  DRM_FORMAT_BGRX1010102 201 
#define  DRM_FORMAT_BGRX4444 200 
#define  DRM_FORMAT_BGRX5551 199 
#define  DRM_FORMAT_BGRX8888 198 
#define  DRM_FORMAT_BGRX8888_A8 197 
#define  DRM_FORMAT_C8 196 
#define  DRM_FORMAT_NV12 195 
#define  DRM_FORMAT_NV16 194 
#define  DRM_FORMAT_NV21 193 
#define  DRM_FORMAT_NV24 192 
#define  DRM_FORMAT_NV42 191 
#define  DRM_FORMAT_NV61 190 
#define  DRM_FORMAT_P010 189 
#define  DRM_FORMAT_P012 188 
#define  DRM_FORMAT_P016 187 
#define  DRM_FORMAT_P210 186 
#define  DRM_FORMAT_RGB332 185 
#define  DRM_FORMAT_RGB565 184 
#define  DRM_FORMAT_RGB565_A8 183 
#define  DRM_FORMAT_RGB888 182 
#define  DRM_FORMAT_RGB888_A8 181 
#define  DRM_FORMAT_RGBA1010102 180 
#define  DRM_FORMAT_RGBA4444 179 
#define  DRM_FORMAT_RGBA5551 178 
#define  DRM_FORMAT_RGBA8888 177 
#define  DRM_FORMAT_RGBX1010102 176 
#define  DRM_FORMAT_RGBX4444 175 
#define  DRM_FORMAT_RGBX5551 174 
#define  DRM_FORMAT_RGBX8888 173 
#define  DRM_FORMAT_RGBX8888_A8 172 
#define  DRM_FORMAT_UYVY 171 
#define  DRM_FORMAT_VUY101010 170 
#define  DRM_FORMAT_VUY888 169 
#define  DRM_FORMAT_VYUY 168 
#define  DRM_FORMAT_X0L0 167 
#define  DRM_FORMAT_X0L2 166 
#define  DRM_FORMAT_XBGR1555 165 
#define  DRM_FORMAT_XBGR16161616F 164 
#define  DRM_FORMAT_XBGR2101010 163 
#define  DRM_FORMAT_XBGR4444 162 
#define  DRM_FORMAT_XBGR8888 161 
#define  DRM_FORMAT_XBGR8888_A8 160 
#define  DRM_FORMAT_XRGB1555 159 
#define  DRM_FORMAT_XRGB16161616F 158 
#define  DRM_FORMAT_XRGB2101010 157 
#define  DRM_FORMAT_XRGB4444 156 
#define  DRM_FORMAT_XRGB8888 155 
#define  DRM_FORMAT_XRGB8888_A8 154 
#define  DRM_FORMAT_XVYU12_16161616 153 
#define  DRM_FORMAT_XVYU16161616 152 
#define  DRM_FORMAT_XVYU2101010 151 
#define  DRM_FORMAT_XYUV8888 150 
#define  DRM_FORMAT_Y0L0 149 
#define  DRM_FORMAT_Y0L2 148 
#define  DRM_FORMAT_Y210 147 
#define  DRM_FORMAT_Y212 146 
#define  DRM_FORMAT_Y216 145 
#define  DRM_FORMAT_Y410 144 
#define  DRM_FORMAT_Y412 143 
#define  DRM_FORMAT_Y416 142 
#define  DRM_FORMAT_YUV410 141 
#define  DRM_FORMAT_YUV411 140 
#define  DRM_FORMAT_YUV420 139 
#define  DRM_FORMAT_YUV420_10BIT 138 
#define  DRM_FORMAT_YUV420_8BIT 137 
#define  DRM_FORMAT_YUV422 136 
#define  DRM_FORMAT_YUV444 135 
#define  DRM_FORMAT_YUYV 134 
#define  DRM_FORMAT_YVU410 133 
#define  DRM_FORMAT_YVU411 132 
#define  DRM_FORMAT_YVU420 131 
#define  DRM_FORMAT_YVU422 130 
#define  DRM_FORMAT_YVU444 129 
#define  DRM_FORMAT_YVYU 128 

const struct drm_format_info *__drm_format_info(u32 format)
{
	static const struct drm_format_info formats[] = {
		{ .format = DRM_FORMAT_C8,		.depth = 8,  .num_planes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGB332,		.depth = 8,  .num_planes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGR233,		.depth = 8,  .num_planes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XRGB4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XBGR4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGBX4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGRX4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_ARGB4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_ABGR4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGBA4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGRA4444,	.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_XRGB1555,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XBGR1555,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGBX5551,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGRX5551,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_ARGB1555,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_ABGR1555,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGBA5551,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGRA5551,	.depth = 15, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGB565,		.depth = 16, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGR565,		.depth = 16, .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGB888,		.depth = 24, .num_planes = 1, .cpp = { 3, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGR888,		.depth = 24, .num_planes = 1, .cpp = { 3, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XRGB8888,	.depth = 24, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XBGR8888,	.depth = 24, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGBX8888,	.depth = 24, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGRX8888,	.depth = 24, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGB565_A8,	.depth = 24, .num_planes = 2, .cpp = { 2, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGR565_A8,	.depth = 24, .num_planes = 2, .cpp = { 2, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_XRGB2101010,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XBGR2101010,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_RGBX1010102,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_BGRX1010102,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_ARGB2101010,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_ABGR2101010,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGBA1010102,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGRA1010102,	.depth = 30, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_ARGB8888,	.depth = 32, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_ABGR8888,	.depth = 32, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGBA8888,	.depth = 32, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGRA8888,	.depth = 32, .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_XRGB16161616F,	.depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_XBGR16161616F,	.depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .format = DRM_FORMAT_ARGB16161616F,	.depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_ABGR16161616F,	.depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGB888_A8,	.depth = 32, .num_planes = 2, .cpp = { 3, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGR888_A8,	.depth = 32, .num_planes = 2, .cpp = { 3, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_XRGB8888_A8,	.depth = 32, .num_planes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_XBGR8888_A8,	.depth = 32, .num_planes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_RGBX8888_A8,	.depth = 32, .num_planes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_BGRX8888_A8,	.depth = 32, .num_planes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true },
		{ .format = DRM_FORMAT_YUV410,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 4, .is_yuv = true },
		{ .format = DRM_FORMAT_YVU410,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 4, .is_yuv = true },
		{ .format = DRM_FORMAT_YUV411,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YVU411,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YUV420,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 2, .is_yuv = true },
		{ .format = DRM_FORMAT_YVU420,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 2, .is_yuv = true },
		{ .format = DRM_FORMAT_YUV422,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YVU422,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YUV444,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YVU444,		.depth = 0,  .num_planes = 3, .cpp = { 1, 1, 1 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_NV12,		.depth = 0,  .num_planes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 2, .is_yuv = true },
		{ .format = DRM_FORMAT_NV21,		.depth = 0,  .num_planes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 2, .is_yuv = true },
		{ .format = DRM_FORMAT_NV16,		.depth = 0,  .num_planes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_NV61,		.depth = 0,  .num_planes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_NV24,		.depth = 0,  .num_planes = 2, .cpp = { 1, 2, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_NV42,		.depth = 0,  .num_planes = 2, .cpp = { 1, 2, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YUYV,		.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_YVYU,		.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_UYVY,		.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_VYUY,		.depth = 0,  .num_planes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_XYUV8888,	.depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_VUY888,          .depth = 0,  .num_planes = 1, .cpp = { 3, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_AYUV,		.depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true },
		{ .format = DRM_FORMAT_Y210,            .depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_Y212,            .depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_Y216,            .depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_Y410,            .depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true },
		{ .format = DRM_FORMAT_Y412,            .depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true },
		{ .format = DRM_FORMAT_Y416,            .depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true },
		{ .format = DRM_FORMAT_XVYU2101010,	.depth = 0,  .num_planes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_XVYU12_16161616,	.depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_XVYU16161616,	.depth = 0,  .num_planes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_Y0L0,		.depth = 0,  .num_planes = 1,
		  .char_per_block = { 8, 0, 0 }, .block_w = { 2, 0, 0 }, .block_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .has_alpha = true, .is_yuv = true },
		{ .format = DRM_FORMAT_X0L0,		.depth = 0,  .num_planes = 1,
		  .char_per_block = { 8, 0, 0 }, .block_w = { 2, 0, 0 }, .block_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = true },
		{ .format = DRM_FORMAT_Y0L2,		.depth = 0,  .num_planes = 1,
		  .char_per_block = { 8, 0, 0 }, .block_w = { 2, 0, 0 }, .block_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .has_alpha = true, .is_yuv = true },
		{ .format = DRM_FORMAT_X0L2,		.depth = 0,  .num_planes = 1,
		  .char_per_block = { 8, 0, 0 }, .block_w = { 2, 0, 0 }, .block_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = true },
		{ .format = DRM_FORMAT_P010,            .depth = 0,  .num_planes = 2,
		  .char_per_block = { 2, 4, 0 }, .block_w = { 1, 0, 0 }, .block_h = { 1, 0, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = true},
		{ .format = DRM_FORMAT_P012,		.depth = 0,  .num_planes = 2,
		  .char_per_block = { 2, 4, 0 }, .block_w = { 1, 0, 0 }, .block_h = { 1, 0, 0 },
		   .hsub = 2, .vsub = 2, .is_yuv = true},
		{ .format = DRM_FORMAT_P016,		.depth = 0,  .num_planes = 2,
		  .char_per_block = { 2, 4, 0 }, .block_w = { 1, 0, 0 }, .block_h = { 1, 0, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = true},
		{ .format = DRM_FORMAT_P210,		.depth = 0,
		  .num_planes = 2, .char_per_block = { 2, 4, 0 },
		  .block_w = { 1, 0, 0 }, .block_h = { 1, 0, 0 }, .hsub = 2,
		  .vsub = 1, .is_yuv = true },
		{ .format = DRM_FORMAT_VUY101010,	.depth = 0,
		  .num_planes = 1, .cpp = { 0, 0, 0 }, .hsub = 1, .vsub = 1,
		  .is_yuv = true },
		{ .format = DRM_FORMAT_YUV420_8BIT,     .depth = 0,
		  .num_planes = 1, .cpp = { 0, 0, 0 }, .hsub = 2, .vsub = 2,
		  .is_yuv = true },
		{ .format = DRM_FORMAT_YUV420_10BIT,    .depth = 0,
		  .num_planes = 1, .cpp = { 0, 0, 0 }, .hsub = 2, .vsub = 2,
		  .is_yuv = true },
	};

	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(formats); ++i) {
		if (formats[i].format == format)
			return &formats[i];
	}

	return NULL;
}