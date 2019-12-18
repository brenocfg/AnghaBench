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
typedef  unsigned int u32 ;
struct v4l2_mbus_framefmt {unsigned int width; int height; int /*<<< orphan*/  code; } ;
struct isp_pipeline {unsigned long l3_ick; int external_rate; int /*<<< orphan*/  max_rate; scalar_t__ input; } ;
struct isp_format_info {int width; } ;
struct isp_device {scalar_t__ revision; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_ccdc_device {struct v4l2_mbus_framefmt* formats; TYPE_1__ subdev; } ;

/* Variables and functions */
 size_t CCDC_PAD_SINK ; 
 size_t CCDC_PAD_SOURCE_VP ; 
 unsigned int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPCCDC_FMTCFG ; 
 unsigned int ISPCCDC_FMTCFG_VPEN ; 
 unsigned int ISPCCDC_FMTCFG_VPIF_FRQ_SHIFT ; 
 unsigned int ISPCCDC_FMTCFG_VPIN_10_1 ; 
 unsigned int ISPCCDC_FMTCFG_VPIN_11_2 ; 
 unsigned int ISPCCDC_FMTCFG_VPIN_12_3 ; 
 unsigned int ISPCCDC_FMTCFG_VPIN_9_0 ; 
 int /*<<< orphan*/  ISPCCDC_FMT_HORZ ; 
 unsigned int ISPCCDC_FMT_HORZ_FMTLNH_SHIFT ; 
 unsigned int ISPCCDC_FMT_HORZ_FMTSPH_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_FMT_VERT ; 
 int ISPCCDC_FMT_VERT_FMTLNV_SHIFT ; 
 int ISPCCDC_FMT_VERT_FMTSLV_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_VP_OUT ; 
 unsigned int ISPCCDC_VP_OUT_HORZ_NUM_SHIFT ; 
 unsigned int ISPCCDC_VP_OUT_VERT_NUM_SHIFT ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_format_info* omap3isp_video_format_info (int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccdc_config_vp(struct isp_ccdc_device *ccdc)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	struct isp_device *isp = to_isp_device(ccdc);
	const struct isp_format_info *info;
	struct v4l2_mbus_framefmt *format;
	unsigned long l3_ick = pipe->l3_ick;
	unsigned int max_div = isp->revision == ISP_REVISION_15_0 ? 64 : 8;
	unsigned int div = 0;
	u32 fmtcfg = ISPCCDC_FMTCFG_VPEN;

	format = &ccdc->formats[CCDC_PAD_SOURCE_VP];

	if (!format->code) {
		/* Disable the video port when the input format isn't supported.
		 * This is indicated by a pixel code set to 0.
		 */
		isp_reg_writel(isp, 0, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMTCFG);
		return;
	}

	isp_reg_writel(isp, (0 << ISPCCDC_FMT_HORZ_FMTSPH_SHIFT) |
		       (format->width << ISPCCDC_FMT_HORZ_FMTLNH_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMT_HORZ);
	isp_reg_writel(isp, (0 << ISPCCDC_FMT_VERT_FMTSLV_SHIFT) |
		       ((format->height + 1) << ISPCCDC_FMT_VERT_FMTLNV_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMT_VERT);

	isp_reg_writel(isp, (format->width << ISPCCDC_VP_OUT_HORZ_NUM_SHIFT) |
		       (format->height << ISPCCDC_VP_OUT_VERT_NUM_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VP_OUT);

	info = omap3isp_video_format_info(ccdc->formats[CCDC_PAD_SINK].code);

	switch (info->width) {
	case 8:
	case 10:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_9_0;
		break;
	case 11:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_10_1;
		break;
	case 12:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_11_2;
		break;
	case 13:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_12_3;
		break;
	}

	if (pipe->input)
		div = DIV_ROUND_UP(l3_ick, pipe->max_rate);
	else if (pipe->external_rate)
		div = l3_ick / pipe->external_rate;

	div = clamp(div, 2U, max_div);
	fmtcfg |= (div - 2) << ISPCCDC_FMTCFG_VPIF_FRQ_SHIFT;

	isp_reg_writel(isp, fmtcfg, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMTCFG);
}