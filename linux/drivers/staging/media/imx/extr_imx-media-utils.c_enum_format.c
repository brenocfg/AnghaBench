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
struct imx_media_pixfmt {size_t fourcc; size_t* codes; int /*<<< orphan*/  bayer; } ;
typedef  enum codespace_sel { ____Placeholder_codespace_sel } codespace_sel ;

/* Variables and functions */
#define  CS_SEL_ANY 130 
#define  CS_SEL_RGB 129 
#define  CS_SEL_YUV 128 
 int EINVAL ; 
 size_t NUM_MBUS_RGB_FORMATS ; 
 size_t NUM_MBUS_YUV_FORMATS ; 
 size_t NUM_RGB_FORMATS ; 
 size_t NUM_YUV_FORMATS ; 
 struct imx_media_pixfmt* rgb_formats ; 
 struct imx_media_pixfmt* yuv_formats ; 

__attribute__((used)) static int enum_format(u32 *fourcc, u32 *code, u32 index,
		       enum codespace_sel cs_sel,
		       bool allow_non_mbus,
		       bool allow_bayer)
{
	const struct imx_media_pixfmt *fmt;
	u32 mbus_yuv_sz = NUM_MBUS_YUV_FORMATS;
	u32 mbus_rgb_sz = NUM_MBUS_RGB_FORMATS;
	u32 yuv_sz = NUM_YUV_FORMATS;
	u32 rgb_sz = NUM_RGB_FORMATS;

	switch (cs_sel) {
	case CS_SEL_YUV:
		if (index >= yuv_sz ||
		    (!allow_non_mbus && index >= mbus_yuv_sz))
			return -EINVAL;
		fmt = &yuv_formats[index];
		break;
	case CS_SEL_RGB:
		if (index >= rgb_sz ||
		    (!allow_non_mbus && index >= mbus_rgb_sz))
			return -EINVAL;
		fmt = &rgb_formats[index];
		if (!allow_bayer && fmt->bayer)
			return -EINVAL;
		break;
	case CS_SEL_ANY:
		if (!allow_non_mbus) {
			if (index >= mbus_yuv_sz) {
				index -= mbus_yuv_sz;
				if (index >= mbus_rgb_sz)
					return -EINVAL;
				fmt = &rgb_formats[index];
				if (!allow_bayer && fmt->bayer)
					return -EINVAL;
			} else {
				fmt = &yuv_formats[index];
			}
		} else {
			if (index >= yuv_sz + rgb_sz)
				return -EINVAL;
			if (index >= yuv_sz) {
				fmt = &rgb_formats[index - yuv_sz];
				if (!allow_bayer && fmt->bayer)
					return -EINVAL;
			} else {
				fmt = &yuv_formats[index];
			}
		}
		break;
	default:
		return -EINVAL;
	}

	if (fourcc)
		*fourcc = fmt->fourcc;
	if (code)
		*code = fmt->codes[0];

	return 0;
}