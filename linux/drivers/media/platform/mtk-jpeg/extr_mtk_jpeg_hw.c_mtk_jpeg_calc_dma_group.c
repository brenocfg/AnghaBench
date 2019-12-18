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
struct mtk_jpeg_dec_param {int src_color; scalar_t__ dst_fourcc; int dma_mcu; int dma_group; int mcu_w; int dma_last_mcu; } ;

/* Variables and functions */
 int MTK_JPEG_COLOR_400 ; 
 int MTK_JPEG_COLOR_422V ; 
 int MTK_JPEG_COLOR_422X2 ; 
 int MTK_JPEG_COLOR_444 ; 
 scalar_t__ V4L2_PIX_FMT_YUV420M ; 
 scalar_t__ V4L2_PIX_FMT_YUV422M ; 

__attribute__((used)) static void mtk_jpeg_calc_dma_group(struct mtk_jpeg_dec_param *param)
{
	u32 factor_mcu = 3;

	if (param->src_color == MTK_JPEG_COLOR_444 &&
	    param->dst_fourcc == V4L2_PIX_FMT_YUV422M)
		factor_mcu = 4;
	else if (param->src_color == MTK_JPEG_COLOR_422V &&
		 param->dst_fourcc == V4L2_PIX_FMT_YUV420M)
		factor_mcu = 4;
	else if (param->src_color == MTK_JPEG_COLOR_422X2 &&
		 param->dst_fourcc == V4L2_PIX_FMT_YUV422M)
		factor_mcu = 2;
	else if (param->src_color == MTK_JPEG_COLOR_400 ||
		 (param->src_color & 0x0FFFF) == 0)
		factor_mcu = 4;

	param->dma_mcu = 1 << factor_mcu;
	param->dma_group = param->mcu_w / param->dma_mcu;
	param->dma_last_mcu = param->mcu_w % param->dma_mcu;
	if (param->dma_last_mcu)
		param->dma_group++;
	else
		param->dma_last_mcu = param->dma_mcu;
}