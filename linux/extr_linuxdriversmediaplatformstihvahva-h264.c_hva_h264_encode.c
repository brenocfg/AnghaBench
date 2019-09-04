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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct hva_stream {int /*<<< orphan*/  bytesused; int /*<<< orphan*/  size; scalar_t__ vaddr; } ;
struct hva_h264_task {int dummy; } ;
struct hva_h264_ctx {int /*<<< orphan*/  rec_frame; int /*<<< orphan*/  ref_frame; TYPE_1__* task; } ;
struct hva_frame {int dummy; } ;
struct hva_ctx {int /*<<< orphan*/  stream_num; scalar_t__ priv; } ;
struct TYPE_2__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  H264_ENC ; 
 int /*<<< orphan*/  hva_h264_fill_data_nal (struct hva_ctx*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hva_h264_get_stream_size (struct hva_h264_task*) ; 
 scalar_t__ hva_h264_get_stuffing_bytes (struct hva_h264_task*) ; 
 int hva_h264_prepare_task (struct hva_ctx*,struct hva_h264_task*,struct hva_frame*,struct hva_stream*) ; 
 int hva_hw_execute_task (struct hva_ctx*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_h264_encode(struct hva_ctx *pctx, struct hva_frame *frame,
			   struct hva_stream *stream)
{
	struct hva_h264_ctx *ctx = (struct hva_h264_ctx *)pctx->priv;
	struct hva_h264_task *task = (struct hva_h264_task *)ctx->task->vaddr;
	u32 stuffing_bytes = 0;
	int ret = 0;

	ret = hva_h264_prepare_task(pctx, task, frame, stream);
	if (ret)
		goto err;

	ret = hva_hw_execute_task(pctx, H264_ENC, ctx->task);
	if (ret)
		goto err;

	pctx->stream_num++;
	stream->bytesused += hva_h264_get_stream_size(task);

	stuffing_bytes = hva_h264_get_stuffing_bytes(task);

	if (stuffing_bytes)
		hva_h264_fill_data_nal(pctx, stuffing_bytes,
				       (u8 *)stream->vaddr,
				       stream->size,
				       &stream->bytesused);

	/* switch reference & reconstructed frame */
	swap(ctx->ref_frame, ctx->rec_frame);

	return 0;
err:
	stream->bytesused = 0;
	return ret;
}