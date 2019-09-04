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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;
struct isp_prev_device {scalar_t__ input; int output; TYPE_1__ params; struct v4l2_mbus_framefmt* formats; } ;
struct isp_format_info {int bpp; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISPPRV_PCR ; 
 int /*<<< orphan*/  ISPPRV_PCR_RSZPORT ; 
 int /*<<< orphan*/  ISPPRV_PCR_SDRPORT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 scalar_t__ PREVIEW_INPUT_CCDC ; 
 int PREVIEW_OUTPUT_MEMORY ; 
 int PREVIEW_OUTPUT_RESIZER ; 
 size_t PREV_PAD_SINK ; 
 size_t PREV_PAD_SOURCE ; 
 int /*<<< orphan*/  isp_reg_clr (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_format_info* omap3isp_video_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_adjust_bandwidth (struct isp_prev_device*) ; 
 int /*<<< orphan*/  preview_config_averager (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_config_inlineoffset (struct isp_prev_device*,int) ; 
 int /*<<< orphan*/  preview_config_input_format (struct isp_prev_device*,struct isp_format_info const*) ; 
 int /*<<< orphan*/  preview_config_input_size (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_config_outlineoffset (struct isp_prev_device*,int) ; 
 int /*<<< orphan*/  preview_config_ycpos (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_params_lock (struct isp_prev_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preview_params_unlock (struct isp_prev_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preview_setup_hw (struct isp_prev_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void preview_configure(struct isp_prev_device *prev)
{
	struct isp_device *isp = to_isp_device(prev);
	const struct isp_format_info *info;
	struct v4l2_mbus_framefmt *format;
	unsigned long flags;
	u32 update;
	u32 active;

	spin_lock_irqsave(&prev->params.lock, flags);
	/* Mark all active parameters we are going to touch as busy. */
	update = preview_params_lock(prev, 0, false);
	active = prev->params.active;
	spin_unlock_irqrestore(&prev->params.lock, flags);

	/* PREV_PAD_SINK */
	format = &prev->formats[PREV_PAD_SINK];
	info = omap3isp_video_format_info(format->code);

	preview_adjust_bandwidth(prev);

	preview_config_input_format(prev, info);
	preview_config_input_size(prev, active);

	if (prev->input == PREVIEW_INPUT_CCDC)
		preview_config_inlineoffset(prev, 0);
	else
		preview_config_inlineoffset(prev, ALIGN(format->width, 0x20) *
					    info->bpp);

	preview_setup_hw(prev, update, active);

	/* PREV_PAD_SOURCE */
	format = &prev->formats[PREV_PAD_SOURCE];

	if (prev->output & PREVIEW_OUTPUT_MEMORY)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SDRPORT);
	else
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SDRPORT);

	if (prev->output & PREVIEW_OUTPUT_RESIZER)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_RSZPORT);
	else
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_RSZPORT);

	if (prev->output & PREVIEW_OUTPUT_MEMORY)
		preview_config_outlineoffset(prev,
				ALIGN(format->width, 0x10) * 2);

	preview_config_averager(prev, 0);
	preview_config_ycpos(prev, format->code);

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_unlock(prev, update, false);
	spin_unlock_irqrestore(&prev->params.lock, flags);
}