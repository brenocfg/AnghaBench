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
struct v4l2_format_info {scalar_t__ format; int mem_planes; int comp_planes; int hdiv; int vdiv; int /*<<< orphan*/  bpp; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct v4l2_format_info const*) ; 
#define  V4L2_PIX_FMT_ABGR32 188 
#define  V4L2_PIX_FMT_ARGB32 187 
#define  V4L2_PIX_FMT_BGR24 186 
#define  V4L2_PIX_FMT_BGR32 185 
#define  V4L2_PIX_FMT_BGRA32 184 
#define  V4L2_PIX_FMT_BGRX32 183 
#define  V4L2_PIX_FMT_GREY 182 
#define  V4L2_PIX_FMT_HSV24 181 
#define  V4L2_PIX_FMT_HSV32 180 
#define  V4L2_PIX_FMT_NV12 179 
#define  V4L2_PIX_FMT_NV12M 178 
#define  V4L2_PIX_FMT_NV16 177 
#define  V4L2_PIX_FMT_NV16M 176 
#define  V4L2_PIX_FMT_NV21 175 
#define  V4L2_PIX_FMT_NV21M 174 
#define  V4L2_PIX_FMT_NV24 173 
#define  V4L2_PIX_FMT_NV42 172 
#define  V4L2_PIX_FMT_NV61 171 
#define  V4L2_PIX_FMT_NV61M 170 
#define  V4L2_PIX_FMT_RGB24 169 
#define  V4L2_PIX_FMT_RGB32 168 
#define  V4L2_PIX_FMT_RGBA32 167 
#define  V4L2_PIX_FMT_RGBX32 166 
#define  V4L2_PIX_FMT_SBGGR10 165 
#define  V4L2_PIX_FMT_SBGGR10ALAW8 164 
#define  V4L2_PIX_FMT_SBGGR10DPCM8 163 
#define  V4L2_PIX_FMT_SBGGR12 162 
#define  V4L2_PIX_FMT_SBGGR8 161 
#define  V4L2_PIX_FMT_SGBRG10 160 
#define  V4L2_PIX_FMT_SGBRG10ALAW8 159 
#define  V4L2_PIX_FMT_SGBRG10DPCM8 158 
#define  V4L2_PIX_FMT_SGBRG12 157 
#define  V4L2_PIX_FMT_SGBRG8 156 
#define  V4L2_PIX_FMT_SGRBG10 155 
#define  V4L2_PIX_FMT_SGRBG10ALAW8 154 
#define  V4L2_PIX_FMT_SGRBG10DPCM8 153 
#define  V4L2_PIX_FMT_SGRBG12 152 
#define  V4L2_PIX_FMT_SGRBG8 151 
#define  V4L2_PIX_FMT_SRGGB10 150 
#define  V4L2_PIX_FMT_SRGGB10ALAW8 149 
#define  V4L2_PIX_FMT_SRGGB10DPCM8 148 
#define  V4L2_PIX_FMT_SRGGB12 147 
#define  V4L2_PIX_FMT_SRGGB8 146 
#define  V4L2_PIX_FMT_UYVY 145 
#define  V4L2_PIX_FMT_VYUY 144 
#define  V4L2_PIX_FMT_XBGR32 143 
#define  V4L2_PIX_FMT_XRGB32 142 
#define  V4L2_PIX_FMT_YUV410 141 
#define  V4L2_PIX_FMT_YUV411P 140 
#define  V4L2_PIX_FMT_YUV420 139 
#define  V4L2_PIX_FMT_YUV420M 138 
#define  V4L2_PIX_FMT_YUV422M 137 
#define  V4L2_PIX_FMT_YUV422P 136 
#define  V4L2_PIX_FMT_YUV444M 135 
#define  V4L2_PIX_FMT_YUYV 134 
#define  V4L2_PIX_FMT_YVU410 133 
#define  V4L2_PIX_FMT_YVU420 132 
#define  V4L2_PIX_FMT_YVU420M 131 
#define  V4L2_PIX_FMT_YVU422M 130 
#define  V4L2_PIX_FMT_YVU444M 129 
#define  V4L2_PIX_FMT_YVYU 128 

const struct v4l2_format_info *v4l2_format_info(u32 format)
{
	static const struct v4l2_format_info formats[] = {
		/* RGB formats */
		{ .format = V4L2_PIX_FMT_BGR24,   .mem_planes = 1, .comp_planes = 1, .bpp = { 3, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_RGB24,   .mem_planes = 1, .comp_planes = 1, .bpp = { 3, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_HSV24,   .mem_planes = 1, .comp_planes = 1, .bpp = { 3, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_BGR32,   .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_XBGR32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_BGRX32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_RGB32,   .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_XRGB32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_RGBX32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_HSV32,   .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_ARGB32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_RGBA32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_ABGR32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_BGRA32,  .mem_planes = 1, .comp_planes = 1, .bpp = { 4, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_GREY,    .mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },

		/* YUV packed formats */
		{ .format = V4L2_PIX_FMT_YUYV,    .mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_YVYU,    .mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_UYVY,    .mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_VYUY,    .mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 2, .vdiv = 1 },

		/* YUV planar formats */
		{ .format = V4L2_PIX_FMT_NV12,    .mem_planes = 1, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_NV21,    .mem_planes = 1, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_NV16,    .mem_planes = 1, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_NV61,    .mem_planes = 1, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_NV24,    .mem_planes = 1, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_NV42,    .mem_planes = 1, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 1, .vdiv = 1 },

		{ .format = V4L2_PIX_FMT_YUV410,  .mem_planes = 1, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 4, .vdiv = 4 },
		{ .format = V4L2_PIX_FMT_YVU410,  .mem_planes = 1, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 4, .vdiv = 4 },
		{ .format = V4L2_PIX_FMT_YUV411P, .mem_planes = 1, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 4, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_YUV420,  .mem_planes = 1, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_YVU420,  .mem_planes = 1, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_YUV422P, .mem_planes = 1, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 1 },

		/* YUV planar formats, non contiguous variant */
		{ .format = V4L2_PIX_FMT_YUV420M, .mem_planes = 3, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_YVU420M, .mem_planes = 3, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_YUV422M, .mem_planes = 3, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_YVU422M, .mem_planes = 3, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_YUV444M, .mem_planes = 3, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_YVU444M, .mem_planes = 3, .comp_planes = 3, .bpp = { 1, 1, 1, 0 }, .hdiv = 1, .vdiv = 1 },

		{ .format = V4L2_PIX_FMT_NV12M,   .mem_planes = 2, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_NV21M,   .mem_planes = 2, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 2 },
		{ .format = V4L2_PIX_FMT_NV16M,   .mem_planes = 2, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_NV61M,   .mem_planes = 2, .comp_planes = 2, .bpp = { 1, 2, 0, 0 }, .hdiv = 2, .vdiv = 1 },

		/* Bayer RGB formats */
		{ .format = V4L2_PIX_FMT_SBGGR8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGBRG8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGRBG8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SRGGB8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SBGGR10,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGBRG10,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGRBG10,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SRGGB10,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SBGGR10ALAW8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGBRG10ALAW8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGRBG10ALAW8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SRGGB10ALAW8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SBGGR10DPCM8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGBRG10DPCM8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGRBG10DPCM8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SRGGB10DPCM8,	.mem_planes = 1, .comp_planes = 1, .bpp = { 1, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SBGGR12,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGBRG12,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SGRBG12,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
		{ .format = V4L2_PIX_FMT_SRGGB12,	.mem_planes = 1, .comp_planes = 1, .bpp = { 2, 0, 0, 0 }, .hdiv = 1, .vdiv = 1 },
	};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(formats); ++i)
		if (formats[i].format == format)
			return &formats[i];
	return NULL;
}