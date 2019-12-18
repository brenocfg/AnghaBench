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
struct vpe_fmt {scalar_t__ fourcc; } ;
struct vpe_ctx {TYPE_2__* dev; TYPE_1__* q_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  vpdma; } ;
struct TYPE_3__ {struct vpe_fmt* fmt; } ;

/* Variables and functions */
 size_t Q_DATA_SRC ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  VPDMA_FSEVENT_CHANNEL_ACTIVE ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA1_IN ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA2_IN ; 
 int /*<<< orphan*/  VPE_CHAN_CHROMA3_IN ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA1_IN ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA2_IN ; 
 int /*<<< orphan*/  VPE_CHAN_LUMA3_IN ; 
 int /*<<< orphan*/  VPE_CHAN_MV_IN ; 
 int /*<<< orphan*/  vpdma_set_frame_start_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpdma_set_line_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_line_modes(struct vpe_ctx *ctx)
{
	struct vpe_fmt *fmt = ctx->q_data[Q_DATA_SRC].fmt;
	int line_mode = 1;

	if (fmt->fourcc == V4L2_PIX_FMT_NV12)
		line_mode = 0;		/* double lines to line buffer */

	/* regs for now */
	vpdma_set_line_mode(ctx->dev->vpdma, line_mode, VPE_CHAN_CHROMA1_IN);
	vpdma_set_line_mode(ctx->dev->vpdma, line_mode, VPE_CHAN_CHROMA2_IN);
	vpdma_set_line_mode(ctx->dev->vpdma, line_mode, VPE_CHAN_CHROMA3_IN);

	/* frame start for input luma */
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_LUMA1_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_LUMA2_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_LUMA3_IN);

	/* frame start for input chroma */
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_CHROMA1_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_CHROMA2_IN);
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_CHROMA3_IN);

	/* frame start for MV in client */
	vpdma_set_frame_start_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEL_ACTIVE,
		VPE_CHAN_MV_IN);
}