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
struct TYPE_8__ {TYPE_3__* m2m_ctx; } ;
struct hantro_ctx {TYPE_4__ fh; } ;
struct TYPE_5__ {int requires_requests; } ;
struct TYPE_6__ {TYPE_1__ q; } ;
struct TYPE_7__ {TYPE_2__ out_q_ctx; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_H264_SLICE 131 
#define  V4L2_PIX_FMT_JPEG 130 
#define  V4L2_PIX_FMT_MPEG2_SLICE 129 
#define  V4L2_PIX_FMT_VP8_FRAME 128 

__attribute__((used)) static void
hantro_update_requires_request(struct hantro_ctx *ctx, u32 fourcc)
{
	switch (fourcc) {
	case V4L2_PIX_FMT_JPEG:
		ctx->fh.m2m_ctx->out_q_ctx.q.requires_requests = false;
		break;
	case V4L2_PIX_FMT_MPEG2_SLICE:
	case V4L2_PIX_FMT_VP8_FRAME:
	case V4L2_PIX_FMT_H264_SLICE:
		ctx->fh.m2m_ctx->out_q_ctx.q.requires_requests = true;
		break;
	default:
		break;
	}
}