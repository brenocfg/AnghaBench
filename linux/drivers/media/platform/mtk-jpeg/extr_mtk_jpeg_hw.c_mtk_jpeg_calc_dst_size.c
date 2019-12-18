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
typedef  size_t u32 ;
struct mtk_jpeg_dec_param {size_t uv_brz_w; size_t comp_num; int mcu_w; int* sampling_w; size_t* comp_w; size_t* img_stride; int* sampling_h; size_t dec_w; size_t dec_h; size_t mcu_h; size_t* mem_stride; size_t* comp_size; size_t y_size; size_t uv_size; size_t dec_size; } ;

/* Variables and functions */
 size_t MTK_JPEG_COMP_MAX ; 
 int MTK_JPEG_DCTSIZE ; 
 void* mtk_jpeg_align (size_t,int) ; 

__attribute__((used)) static int mtk_jpeg_calc_dst_size(struct mtk_jpeg_dec_param *param)
{
	u32 i, padding_w;
	u32 ds_row_h[3];
	u32 brz_w[3];

	brz_w[0] = 0;
	brz_w[1] = param->uv_brz_w;
	brz_w[2] = brz_w[1];

	for (i = 0; i < param->comp_num; i++) {
		if (brz_w[i] > 3)
			return -1;

		padding_w = param->mcu_w * MTK_JPEG_DCTSIZE *
				param->sampling_w[i];
		/* output format is 420/422 */
		param->comp_w[i] = padding_w >> brz_w[i];
		param->comp_w[i] = mtk_jpeg_align(param->comp_w[i],
						  MTK_JPEG_DCTSIZE);
		param->img_stride[i] = i ? mtk_jpeg_align(param->comp_w[i], 16)
					: mtk_jpeg_align(param->comp_w[i], 32);
		ds_row_h[i] = (MTK_JPEG_DCTSIZE * param->sampling_h[i]);
	}
	param->dec_w = param->img_stride[0];
	param->dec_h = ds_row_h[0] * param->mcu_h;

	for (i = 0; i < MTK_JPEG_COMP_MAX; i++) {
		/* They must be equal in frame mode. */
		param->mem_stride[i] = param->img_stride[i];
		param->comp_size[i] = param->mem_stride[i] * ds_row_h[i] *
				      param->mcu_h;
	}

	param->y_size = param->comp_size[0];
	param->uv_size = param->comp_size[1];
	param->dec_size = param->y_size + (param->uv_size << 1);

	return 0;
}