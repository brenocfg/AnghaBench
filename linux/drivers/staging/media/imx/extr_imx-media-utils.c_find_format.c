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
typedef  int /*<<< orphan*/  u32 ;
struct imx_media_pixfmt {int dummy; } ;
typedef  enum codespace_sel { ____Placeholder_codespace_sel } codespace_sel ;

/* Variables and functions */
#define  CS_SEL_ANY 130 
#define  CS_SEL_RGB 129 
#define  CS_SEL_YUV 128 
 int /*<<< orphan*/  NUM_RGB_FORMATS ; 
 int /*<<< orphan*/  NUM_YUV_FORMATS ; 
 struct imx_media_pixfmt const* __find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgb_formats ; 
 int /*<<< orphan*/  yuv_formats ; 

__attribute__((used)) static const struct imx_media_pixfmt *find_format(u32 fourcc,
						  u32 code,
						  enum codespace_sel cs_sel,
						  bool allow_non_mbus,
						  bool allow_bayer)
{
	const struct imx_media_pixfmt *ret;

	switch (cs_sel) {
	case CS_SEL_YUV:
		return __find_format(fourcc, code, allow_non_mbus, allow_bayer,
				     yuv_formats, NUM_YUV_FORMATS);
	case CS_SEL_RGB:
		return __find_format(fourcc, code, allow_non_mbus, allow_bayer,
				     rgb_formats, NUM_RGB_FORMATS);
	case CS_SEL_ANY:
		ret = __find_format(fourcc, code, allow_non_mbus, allow_bayer,
				    yuv_formats, NUM_YUV_FORMATS);
		if (ret)
			return ret;
		return __find_format(fourcc, code, allow_non_mbus, allow_bayer,
				     rgb_formats, NUM_RGB_FORMATS);
	default:
		return NULL;
	}
}