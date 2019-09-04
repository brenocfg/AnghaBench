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
struct tpg_data {int fourcc; int planes; int buffers; int recalc_colors; int interleaved; int* vdownsampling; int* hdownsampling; int* hmask; int* twopixelsize; void* color_enc; } ;

/* Variables and functions */
 void* TGP_COLOR_ENC_HSV ; 
 void* TGP_COLOR_ENC_LUMA ; 
 void* TGP_COLOR_ENC_RGB ; 
 void* TGP_COLOR_ENC_YCBCR ; 
#define  V4L2_PIX_FMT_ABGR32 194 
#define  V4L2_PIX_FMT_ARGB32 193 
#define  V4L2_PIX_FMT_ARGB444 192 
#define  V4L2_PIX_FMT_ARGB555 191 
#define  V4L2_PIX_FMT_ARGB555X 190 
#define  V4L2_PIX_FMT_BGR24 189 
#define  V4L2_PIX_FMT_BGR32 188 
#define  V4L2_PIX_FMT_BGR666 187 
#define  V4L2_PIX_FMT_GREY 186 
#define  V4L2_PIX_FMT_HSV24 185 
#define  V4L2_PIX_FMT_HSV32 184 
#define  V4L2_PIX_FMT_NV12 183 
#define  V4L2_PIX_FMT_NV12M 182 
#define  V4L2_PIX_FMT_NV16 181 
#define  V4L2_PIX_FMT_NV16M 180 
#define  V4L2_PIX_FMT_NV21 179 
#define  V4L2_PIX_FMT_NV21M 178 
#define  V4L2_PIX_FMT_NV24 177 
#define  V4L2_PIX_FMT_NV42 176 
#define  V4L2_PIX_FMT_NV61 175 
#define  V4L2_PIX_FMT_NV61M 174 
#define  V4L2_PIX_FMT_RGB24 173 
#define  V4L2_PIX_FMT_RGB32 172 
#define  V4L2_PIX_FMT_RGB332 171 
#define  V4L2_PIX_FMT_RGB444 170 
#define  V4L2_PIX_FMT_RGB555 169 
#define  V4L2_PIX_FMT_RGB555X 168 
#define  V4L2_PIX_FMT_RGB565 167 
#define  V4L2_PIX_FMT_RGB565X 166 
#define  V4L2_PIX_FMT_SBGGR10 165 
#define  V4L2_PIX_FMT_SBGGR12 164 
#define  V4L2_PIX_FMT_SBGGR8 163 
#define  V4L2_PIX_FMT_SGBRG10 162 
#define  V4L2_PIX_FMT_SGBRG12 161 
#define  V4L2_PIX_FMT_SGBRG8 160 
#define  V4L2_PIX_FMT_SGRBG10 159 
#define  V4L2_PIX_FMT_SGRBG12 158 
#define  V4L2_PIX_FMT_SGRBG8 157 
#define  V4L2_PIX_FMT_SRGGB10 156 
#define  V4L2_PIX_FMT_SRGGB12 155 
#define  V4L2_PIX_FMT_SRGGB8 154 
#define  V4L2_PIX_FMT_UYVY 153 
#define  V4L2_PIX_FMT_VYUY 152 
#define  V4L2_PIX_FMT_XBGR32 151 
#define  V4L2_PIX_FMT_XRGB32 150 
#define  V4L2_PIX_FMT_XRGB444 149 
#define  V4L2_PIX_FMT_XRGB555 148 
#define  V4L2_PIX_FMT_XRGB555X 147 
#define  V4L2_PIX_FMT_Y10 146 
#define  V4L2_PIX_FMT_Y12 145 
#define  V4L2_PIX_FMT_Y16 144 
#define  V4L2_PIX_FMT_Y16_BE 143 
#define  V4L2_PIX_FMT_YUV32 142 
#define  V4L2_PIX_FMT_YUV420 141 
#define  V4L2_PIX_FMT_YUV420M 140 
#define  V4L2_PIX_FMT_YUV422M 139 
#define  V4L2_PIX_FMT_YUV422P 138 
#define  V4L2_PIX_FMT_YUV444 137 
#define  V4L2_PIX_FMT_YUV444M 136 
#define  V4L2_PIX_FMT_YUV555 135 
#define  V4L2_PIX_FMT_YUV565 134 
#define  V4L2_PIX_FMT_YUYV 133 
#define  V4L2_PIX_FMT_YVU420 132 
#define  V4L2_PIX_FMT_YVU420M 131 
#define  V4L2_PIX_FMT_YVU422M 130 
#define  V4L2_PIX_FMT_YVU444M 129 
#define  V4L2_PIX_FMT_YVYU 128 

bool tpg_s_fourcc(struct tpg_data *tpg, u32 fourcc)
{
	tpg->fourcc = fourcc;
	tpg->planes = 1;
	tpg->buffers = 1;
	tpg->recalc_colors = true;
	tpg->interleaved = false;
	tpg->vdownsampling[0] = 1;
	tpg->hdownsampling[0] = 1;
	tpg->hmask[0] = ~0;
	tpg->hmask[1] = ~0;
	tpg->hmask[2] = ~0;

	switch (fourcc) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
		tpg->interleaved = true;
		tpg->vdownsampling[1] = 1;
		tpg->hdownsampling[1] = 1;
		tpg->planes = 2;
		/* fall through */
	case V4L2_PIX_FMT_RGB332:
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
	case V4L2_PIX_FMT_RGB444:
	case V4L2_PIX_FMT_XRGB444:
	case V4L2_PIX_FMT_ARGB444:
	case V4L2_PIX_FMT_RGB555:
	case V4L2_PIX_FMT_XRGB555:
	case V4L2_PIX_FMT_ARGB555:
	case V4L2_PIX_FMT_RGB555X:
	case V4L2_PIX_FMT_XRGB555X:
	case V4L2_PIX_FMT_ARGB555X:
	case V4L2_PIX_FMT_BGR666:
	case V4L2_PIX_FMT_RGB24:
	case V4L2_PIX_FMT_BGR24:
	case V4L2_PIX_FMT_RGB32:
	case V4L2_PIX_FMT_BGR32:
	case V4L2_PIX_FMT_XRGB32:
	case V4L2_PIX_FMT_XBGR32:
	case V4L2_PIX_FMT_ARGB32:
	case V4L2_PIX_FMT_ABGR32:
		tpg->color_enc = TGP_COLOR_ENC_RGB;
		break;
	case V4L2_PIX_FMT_GREY:
	case V4L2_PIX_FMT_Y10:
	case V4L2_PIX_FMT_Y12:
	case V4L2_PIX_FMT_Y16:
	case V4L2_PIX_FMT_Y16_BE:
		tpg->color_enc = TGP_COLOR_ENC_LUMA;
		break;
	case V4L2_PIX_FMT_YUV444:
	case V4L2_PIX_FMT_YUV555:
	case V4L2_PIX_FMT_YUV565:
	case V4L2_PIX_FMT_YUV32:
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_YUV420M:
	case V4L2_PIX_FMT_YVU420M:
		tpg->buffers = 3;
		/* fall through */
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
		tpg->vdownsampling[1] = 2;
		tpg->vdownsampling[2] = 2;
		tpg->hdownsampling[1] = 2;
		tpg->hdownsampling[2] = 2;
		tpg->planes = 3;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_YUV422M:
	case V4L2_PIX_FMT_YVU422M:
		tpg->buffers = 3;
		/* fall through */
	case V4L2_PIX_FMT_YUV422P:
		tpg->vdownsampling[1] = 1;
		tpg->vdownsampling[2] = 1;
		tpg->hdownsampling[1] = 2;
		tpg->hdownsampling[2] = 2;
		tpg->planes = 3;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_NV16M:
	case V4L2_PIX_FMT_NV61M:
		tpg->buffers = 2;
		/* fall through */
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		tpg->vdownsampling[1] = 1;
		tpg->hdownsampling[1] = 1;
		tpg->hmask[1] = ~1;
		tpg->planes = 2;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_NV12M:
	case V4L2_PIX_FMT_NV21M:
		tpg->buffers = 2;
		/* fall through */
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		tpg->vdownsampling[1] = 2;
		tpg->hdownsampling[1] = 1;
		tpg->hmask[1] = ~1;
		tpg->planes = 2;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_YUV444M:
	case V4L2_PIX_FMT_YVU444M:
		tpg->buffers = 3;
		tpg->planes = 3;
		tpg->vdownsampling[1] = 1;
		tpg->vdownsampling[2] = 1;
		tpg->hdownsampling[1] = 1;
		tpg->hdownsampling[2] = 1;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_NV24:
	case V4L2_PIX_FMT_NV42:
		tpg->vdownsampling[1] = 1;
		tpg->hdownsampling[1] = 1;
		tpg->planes = 2;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_VYUY:
		tpg->hmask[0] = ~1;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		break;
	case V4L2_PIX_FMT_HSV24:
	case V4L2_PIX_FMT_HSV32:
		tpg->color_enc = TGP_COLOR_ENC_HSV;
		break;
	default:
		return false;
	}

	switch (fourcc) {
	case V4L2_PIX_FMT_GREY:
	case V4L2_PIX_FMT_RGB332:
		tpg->twopixelsize[0] = 2;
		break;
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
	case V4L2_PIX_FMT_RGB444:
	case V4L2_PIX_FMT_XRGB444:
	case V4L2_PIX_FMT_ARGB444:
	case V4L2_PIX_FMT_RGB555:
	case V4L2_PIX_FMT_XRGB555:
	case V4L2_PIX_FMT_ARGB555:
	case V4L2_PIX_FMT_RGB555X:
	case V4L2_PIX_FMT_XRGB555X:
	case V4L2_PIX_FMT_ARGB555X:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_VYUY:
	case V4L2_PIX_FMT_YUV444:
	case V4L2_PIX_FMT_YUV555:
	case V4L2_PIX_FMT_YUV565:
	case V4L2_PIX_FMT_Y10:
	case V4L2_PIX_FMT_Y12:
	case V4L2_PIX_FMT_Y16:
	case V4L2_PIX_FMT_Y16_BE:
		tpg->twopixelsize[0] = 2 * 2;
		break;
	case V4L2_PIX_FMT_RGB24:
	case V4L2_PIX_FMT_BGR24:
	case V4L2_PIX_FMT_HSV24:
		tpg->twopixelsize[0] = 2 * 3;
		break;
	case V4L2_PIX_FMT_BGR666:
	case V4L2_PIX_FMT_RGB32:
	case V4L2_PIX_FMT_BGR32:
	case V4L2_PIX_FMT_XRGB32:
	case V4L2_PIX_FMT_XBGR32:
	case V4L2_PIX_FMT_ARGB32:
	case V4L2_PIX_FMT_ABGR32:
	case V4L2_PIX_FMT_YUV32:
	case V4L2_PIX_FMT_HSV32:
		tpg->twopixelsize[0] = 2 * 4;
		break;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV12M:
	case V4L2_PIX_FMT_NV21M:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_NV16M:
	case V4L2_PIX_FMT_NV61M:
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
		tpg->twopixelsize[0] = 2;
		tpg->twopixelsize[1] = 2;
		break;
	case V4L2_PIX_FMT_SRGGB10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SRGGB12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SBGGR12:
		tpg->twopixelsize[0] = 4;
		tpg->twopixelsize[1] = 4;
		break;
	case V4L2_PIX_FMT_YUV444M:
	case V4L2_PIX_FMT_YVU444M:
	case V4L2_PIX_FMT_YUV422M:
	case V4L2_PIX_FMT_YVU422M:
	case V4L2_PIX_FMT_YUV422P:
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
	case V4L2_PIX_FMT_YUV420M:
	case V4L2_PIX_FMT_YVU420M:
		tpg->twopixelsize[0] = 2;
		tpg->twopixelsize[1] = 2;
		tpg->twopixelsize[2] = 2;
		break;
	case V4L2_PIX_FMT_NV24:
	case V4L2_PIX_FMT_NV42:
		tpg->twopixelsize[0] = 2;
		tpg->twopixelsize[1] = 4;
		break;
	}
	return true;
}