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
struct imx_media_pixfmt {int* codes; } ;
typedef  enum codespace_sel { ____Placeholder_codespace_sel } codespace_sel ;

/* Variables and functions */
#define  CS_SEL_ANY 130 
#define  CS_SEL_RGB 129 
#define  CS_SEL_YUV 128 
 int NUM_IPU_RGB_FORMATS ; 
 int NUM_IPU_YUV_FORMATS ; 
 struct imx_media_pixfmt* ipu_rgb_formats ; 
 struct imx_media_pixfmt* ipu_yuv_formats ; 

const struct imx_media_pixfmt *
imx_media_find_ipu_format(u32 code, enum codespace_sel cs_sel)
{
	const struct imx_media_pixfmt *array, *fmt, *ret = NULL;
	u32 array_size;
	int i, j;

	switch (cs_sel) {
	case CS_SEL_YUV:
		array_size = NUM_IPU_YUV_FORMATS;
		array = ipu_yuv_formats;
		break;
	case CS_SEL_RGB:
		array_size = NUM_IPU_RGB_FORMATS;
		array = ipu_rgb_formats;
		break;
	case CS_SEL_ANY:
		array_size = NUM_IPU_YUV_FORMATS + NUM_IPU_RGB_FORMATS;
		array = ipu_yuv_formats;
		break;
	default:
		return NULL;
	}

	for (i = 0; i < array_size; i++) {
		if (cs_sel == CS_SEL_ANY && i >= NUM_IPU_YUV_FORMATS)
			fmt = &ipu_rgb_formats[i - NUM_IPU_YUV_FORMATS];
		else
			fmt = &array[i];

		for (j = 0; code && fmt->codes[j]; j++) {
			if (code == fmt->codes[j]) {
				ret = fmt;
				goto out;
			}
		}
	}

out:
	return ret;
}