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
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix_mp; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct s5p_mfc_ctx {void* dst_fmt; void* src_fmt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_MFCV6_PLUS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MFCV8_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFC_FMT_DEC ; 
 int /*<<< orphan*/  MFC_FMT_RAW ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12M ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12MT ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12MT_16X16 ; 
 void* find_format (struct v4l2_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,void*,void*) ; 

void s5p_mfc_dec_init(struct s5p_mfc_ctx *ctx)
{
	struct v4l2_format f;
	f.fmt.pix_mp.pixelformat = V4L2_PIX_FMT_H264;
	ctx->src_fmt = find_format(&f, MFC_FMT_DEC);
	if (IS_MFCV8_PLUS(ctx->dev))
		f.fmt.pix_mp.pixelformat = V4L2_PIX_FMT_NV12M;
	else if (IS_MFCV6_PLUS(ctx->dev))
		f.fmt.pix_mp.pixelformat = V4L2_PIX_FMT_NV12MT_16X16;
	else
		f.fmt.pix_mp.pixelformat = V4L2_PIX_FMT_NV12MT;
	ctx->dst_fmt = find_format(&f, MFC_FMT_RAW);
	mfc_debug(2, "Default src_fmt is %p, dest_fmt is %p\n",
			ctx->src_fmt, ctx->dst_fmt);
}