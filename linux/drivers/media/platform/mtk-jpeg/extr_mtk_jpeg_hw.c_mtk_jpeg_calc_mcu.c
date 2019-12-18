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
struct mtk_jpeg_dec_param {int* sampling_w; int* sampling_h; int mcu_w; int pic_w; int mcu_h; int pic_h; int total_mcu; int unit_num; int blk_num; int* blk_comp; int comp_num; int membership; } ;

/* Variables and functions */
 int MTK_JPEG_BLOCK_MAX ; 
 int MTK_JPEG_COMP_MAX ; 

__attribute__((used)) static void mtk_jpeg_calc_mcu(struct mtk_jpeg_dec_param *param)
{
	u32 factor_w, factor_h;
	u32 i, comp, blk;

	factor_w = 2 + param->sampling_w[0];
	factor_h = 2 + param->sampling_h[0];
	param->mcu_w = (param->pic_w + (1 << factor_w) - 1) >> factor_w;
	param->mcu_h = (param->pic_h + (1 << factor_h) - 1) >> factor_h;
	param->total_mcu = param->mcu_w * param->mcu_h;
	param->unit_num = ((param->pic_w + 7) >> 3) * ((param->pic_h + 7) >> 3);
	param->blk_num = 0;
	for (i = 0; i < MTK_JPEG_COMP_MAX; i++) {
		param->blk_comp[i] = 0;
		if (i >= param->comp_num)
			continue;
		param->blk_comp[i] = param->sampling_w[i] *
				     param->sampling_h[i];
		param->blk_num += param->blk_comp[i];
	}

	param->membership = 0;
	for (i = 0, blk = 0, comp = 0; i < MTK_JPEG_BLOCK_MAX; i++) {
		if (i < param->blk_num && comp < param->comp_num) {
			u32 tmp;

			tmp = (0x04 + (comp & 0x3));
			param->membership |= tmp << (i * 3);
			if (++blk == param->blk_comp[comp]) {
				comp++;
				blk = 0;
			}
		} else {
			param->membership |=  7 << (i * 3);
		}
	}
}