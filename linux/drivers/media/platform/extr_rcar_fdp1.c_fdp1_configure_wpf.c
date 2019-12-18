#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int num_planes; scalar_t__ ycbcr_enc; scalar_t__ quantization; TYPE_1__* plane_fmt; } ;
struct fdp1_q_data {TYPE_4__* fmt; TYPE_2__ format; } ;
struct fdp1_job {TYPE_3__* dst; } ;
struct fdp1_dev {int dummy; } ;
struct fdp1_ctx {int alpha; struct fdp1_q_data cap_q; struct fdp1_q_data out_q; struct fdp1_dev* fdp1; } ;
struct TYPE_8__ {int fmt; int swap; scalar_t__ swap_uv; scalar_t__ swap_yc; } ;
struct TYPE_7__ {int* addrs; } ;
struct TYPE_5__ {int bytesperline; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD1_WPF_ADDR_C0 ; 
 int /*<<< orphan*/  FD1_WPF_ADDR_C1 ; 
 int /*<<< orphan*/  FD1_WPF_ADDR_Y ; 
 int /*<<< orphan*/  FD1_WPF_FORMAT ; 
 int FD1_WPF_FORMAT_CSC ; 
 int FD1_WPF_FORMAT_PDV_SHIFT ; 
 int FD1_WPF_FORMAT_WRTM_601_0 ; 
 int FD1_WPF_FORMAT_WRTM_601_16 ; 
 int FD1_WPF_FORMAT_WRTM_709_16 ; 
 int FD1_WPF_FORMAT_WSPUVS ; 
 int FD1_WPF_FORMAT_WSPYCS ; 
 int /*<<< orphan*/  FD1_WPF_PSTRIDE ; 
 int FD1_WPF_PSTRIDE_C_SHIFT ; 
 int FD1_WPF_PSTRIDE_Y_SHIFT ; 
 int /*<<< orphan*/  FD1_WPF_RNDCTL ; 
 int FD1_WPF_RNDCTL_CBRM ; 
 int FD1_WPF_RNDCTL_CLMD_NOCLIP ; 
 int /*<<< orphan*/  FD1_WPF_SWAP ; 
 int FD1_WPF_SWAP_OSWAP_SHIFT ; 
 int FD1_WPF_SWAP_SSWAP_SHIFT ; 
 scalar_t__ V4L2_QUANTIZATION_FULL_RANGE ; 
 scalar_t__ V4L2_YCBCR_ENC_709 ; 
 scalar_t__ fdp1_fmt_is_rgb (TYPE_4__*) ; 
 int /*<<< orphan*/  fdp1_write (struct fdp1_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_configure_wpf(struct fdp1_ctx *ctx,
			       struct fdp1_job *job)
{
	struct fdp1_dev *fdp1 = ctx->fdp1;
	struct fdp1_q_data *src_q_data = &ctx->out_q;
	struct fdp1_q_data *q_data = &ctx->cap_q;
	u32 pstride;
	u32 format;
	u32 swap;
	u32 rndctl;

	pstride = q_data->format.plane_fmt[0].bytesperline
		<< FD1_WPF_PSTRIDE_Y_SHIFT;

	if (q_data->format.num_planes > 1)
		pstride |= q_data->format.plane_fmt[1].bytesperline
			<< FD1_WPF_PSTRIDE_C_SHIFT;

	format = q_data->fmt->fmt; /* Output Format Code */

	if (q_data->fmt->swap_yc)
		format |= FD1_WPF_FORMAT_WSPYCS;

	if (q_data->fmt->swap_uv)
		format |= FD1_WPF_FORMAT_WSPUVS;

	if (fdp1_fmt_is_rgb(q_data->fmt)) {
		/* Enable Colour Space conversion */
		format |= FD1_WPF_FORMAT_CSC;

		/* Set WRTM */
		if (src_q_data->format.ycbcr_enc == V4L2_YCBCR_ENC_709)
			format |= FD1_WPF_FORMAT_WRTM_709_16;
		else if (src_q_data->format.quantization ==
				V4L2_QUANTIZATION_FULL_RANGE)
			format |= FD1_WPF_FORMAT_WRTM_601_0;
		else
			format |= FD1_WPF_FORMAT_WRTM_601_16;
	}

	/* Set an alpha value into the Pad Value */
	format |= ctx->alpha << FD1_WPF_FORMAT_PDV_SHIFT;

	/* Determine picture rounding and clipping */
	rndctl = FD1_WPF_RNDCTL_CBRM; /* Rounding Off */
	rndctl |= FD1_WPF_RNDCTL_CLMD_NOCLIP;

	/* WPF Swap needs both ISWAP and OSWAP setting */
	swap = q_data->fmt->swap << FD1_WPF_SWAP_OSWAP_SHIFT;
	swap |= src_q_data->fmt->swap << FD1_WPF_SWAP_SSWAP_SHIFT;

	fdp1_write(fdp1, format, FD1_WPF_FORMAT);
	fdp1_write(fdp1, rndctl, FD1_WPF_RNDCTL);
	fdp1_write(fdp1, swap, FD1_WPF_SWAP);
	fdp1_write(fdp1, pstride, FD1_WPF_PSTRIDE);

	fdp1_write(fdp1, job->dst->addrs[0], FD1_WPF_ADDR_Y);
	fdp1_write(fdp1, job->dst->addrs[1], FD1_WPF_ADDR_C0);
	fdp1_write(fdp1, job->dst->addrs[2], FD1_WPF_ADDR_C1);
}