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
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {scalar_t__ inst_type; int bit_stream_param; int num_metas; int num_internal_frames; TYPE_2__* dev; scalar_t__ aborting; int /*<<< orphan*/  idx; scalar_t__ hold; int /*<<< orphan*/  frm_dis_flg; scalar_t__ use_vdoa; scalar_t__ use_bit; TYPE_1__ fh; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int CODA_BIT_STREAM_END_FLAG ; 
 scalar_t__ CODA_INST_DECODER ; 
 int /*<<< orphan*/  coda_debug ; 
 int coda_get_bitstream_payload (struct coda_ctx*) ; 
 unsigned int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_m2m_num_dst_bufs_ready (int /*<<< orphan*/ ) ; 
 int v4l2_m2m_num_src_bufs_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_job_ready(void *m2m_priv)
{
	struct coda_ctx *ctx = m2m_priv;
	int src_bufs = v4l2_m2m_num_src_bufs_ready(ctx->fh.m2m_ctx);

	/*
	 * For both 'P' and 'key' frame cases 1 picture
	 * and 1 frame are needed. In the decoder case,
	 * the compressed frame can be in the bitstream.
	 */
	if (!src_bufs && ctx->inst_type != CODA_INST_DECODER) {
		v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
			 "not ready: not enough video buffers.\n");
		return 0;
	}

	if (!v4l2_m2m_num_dst_bufs_ready(ctx->fh.m2m_ctx)) {
		v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
			 "not ready: not enough video capture buffers.\n");
		return 0;
	}

	if (ctx->inst_type == CODA_INST_DECODER && ctx->use_bit) {
		bool stream_end = ctx->bit_stream_param &
				  CODA_BIT_STREAM_END_FLAG;
		int num_metas = ctx->num_metas;
		unsigned int count;

		count = hweight32(ctx->frm_dis_flg);
		if (ctx->use_vdoa && count >= (ctx->num_internal_frames - 1)) {
			v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
				 "%d: not ready: all internal buffers in use: %d/%d (0x%x)",
				 ctx->idx, count, ctx->num_internal_frames,
				 ctx->frm_dis_flg);
			return 0;
		}

		if (ctx->hold && !src_bufs) {
			v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
				 "%d: not ready: on hold for more buffers.\n",
				 ctx->idx);
			return 0;
		}

		if (!stream_end && (num_metas + src_bufs) < 2) {
			v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
				 "%d: not ready: need 2 buffers available (%d, %d)\n",
				 ctx->idx, num_metas, src_bufs);
			return 0;
		}


		if (!src_bufs && !stream_end &&
		    (coda_get_bitstream_payload(ctx) < 512)) {
			v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
				 "%d: not ready: not enough bitstream data (%d).\n",
				 ctx->idx, coda_get_bitstream_payload(ctx));
			return 0;
		}
	}

	if (ctx->aborting) {
		v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
			 "not ready: aborting\n");
		return 0;
	}

	v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev,
			"job ready\n");

	return 1;
}