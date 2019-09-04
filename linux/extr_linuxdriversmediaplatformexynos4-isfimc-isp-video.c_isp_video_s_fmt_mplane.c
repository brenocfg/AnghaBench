#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct param_dma_output {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  bitwidth; int /*<<< orphan*/  plane; int /*<<< orphan*/  order; int /*<<< orphan*/  format; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pixfmt; struct fimc_fmt const* format; } ;
struct fimc_isp {TYPE_2__ video_capture; } ;
struct fimc_is {int dummy; } ;
struct fimc_fmt {int /*<<< orphan*/ * depth; int /*<<< orphan*/  memplanes; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_OUTPUT_FORMAT_BAYER ; 
 int /*<<< orphan*/  DMA_OUTPUT_ORDER_GB_BG ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct param_dma_output* __get_isp_dma2 (struct fimc_is*) ; 
 int /*<<< orphan*/  __isp_video_try_fmt (struct fimc_isp*,struct v4l2_pix_format_mplane*,struct fimc_fmt const**) ; 
 int /*<<< orphan*/  fimc_is_mem_barrier () ; 
 struct fimc_is* fimc_isp_to_is (struct fimc_isp*) ; 
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_s_fmt_mplane(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct fimc_isp *isp = video_drvdata(file);
	struct fimc_is *is = fimc_isp_to_is(isp);
	struct v4l2_pix_format_mplane *pixm = &f->fmt.pix_mp;
	const struct fimc_fmt *ifmt = NULL;
	struct param_dma_output *dma = __get_isp_dma2(is);

	__isp_video_try_fmt(isp, pixm, &ifmt);

	if (WARN_ON(ifmt == NULL))
		return -EINVAL;

	dma->format = DMA_OUTPUT_FORMAT_BAYER;
	dma->order = DMA_OUTPUT_ORDER_GB_BG;
	dma->plane = ifmt->memplanes;
	dma->bitwidth = ifmt->depth[0];
	dma->width = pixm->width;
	dma->height = pixm->height;

	fimc_is_mem_barrier();

	isp->video_capture.format = ifmt;
	isp->video_capture.pixfmt = *pixm;

	return 0;
}