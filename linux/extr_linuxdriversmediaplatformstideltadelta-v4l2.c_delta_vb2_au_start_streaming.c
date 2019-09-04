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
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {TYPE_2__ vb2_buf; } ;
struct vb2_queue {int dummy; } ;
struct delta_streaminfo {int /*<<< orphan*/  dts; int /*<<< orphan*/  size; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  streamformat; } ;
struct delta_frameinfo {int /*<<< orphan*/  dts; int /*<<< orphan*/  size; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  streamformat; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
typedef  struct delta_dec const delta_dec ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {scalar_t__ state; TYPE_1__ fh; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; struct delta_dec const* dec; struct delta_streaminfo frameinfo; struct delta_streaminfo streaminfo; struct delta_dev* dev; } ;
struct delta_au {int /*<<< orphan*/  dts; int /*<<< orphan*/  size; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  streamformat; } ;
typedef  int /*<<< orphan*/  str2 ;
typedef  int /*<<< orphan*/  str1 ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_FLAG_FRAMEINFO ; 
 int /*<<< orphan*/  DELTA_FLAG_STREAMINFO ; 
 scalar_t__ DELTA_STATE_READY ; 
 scalar_t__ DELTA_STATE_WF_FORMAT ; 
 scalar_t__ DELTA_STATE_WF_STREAMINFO ; 
 int EINVAL ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int call_dec_op (struct delta_dec const*,int /*<<< orphan*/ ,struct delta_ctx*,struct delta_streaminfo*) ; 
 int /*<<< orphan*/  decode ; 
 int /*<<< orphan*/  delta_au_done (struct delta_ctx*,struct delta_streaminfo*,int) ; 
 int /*<<< orphan*/  delta_frameinfo_str (struct delta_streaminfo*,unsigned char*,int) ; 
 int delta_open_decoder (struct delta_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct delta_dec const**) ; 
 int /*<<< orphan*/  delta_push_dts (struct delta_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delta_streaminfo_str (struct delta_streaminfo*,unsigned char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dump_au (struct delta_ctx*,struct delta_streaminfo*) ; 
 int /*<<< orphan*/  get_frameinfo ; 
 int /*<<< orphan*/  get_streaminfo ; 
 struct delta_streaminfo* to_au (struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct delta_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_get_plane_payload (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delta_vb2_au_start_streaming(struct vb2_queue *q,
					unsigned int count)
{
	struct delta_ctx *ctx = vb2_get_drv_priv(q);
	struct delta_dev *delta = ctx->dev;
	const struct delta_dec *dec = ctx->dec;
	struct delta_au *au;
	int ret = 0;
	struct vb2_v4l2_buffer *vbuf = NULL;
	struct delta_streaminfo *streaminfo = &ctx->streaminfo;
	struct delta_frameinfo *frameinfo = &ctx->frameinfo;
	unsigned char str1[100] = "";
	unsigned char str2[100] = "";

	if ((ctx->state != DELTA_STATE_WF_FORMAT) &&
	    (ctx->state != DELTA_STATE_WF_STREAMINFO))
		return 0;

	if (ctx->state == DELTA_STATE_WF_FORMAT) {
		/* open decoder if not yet done */
		ret = delta_open_decoder(ctx,
					 ctx->streaminfo.streamformat,
					 ctx->frameinfo.pixelformat, &dec);
		if (ret)
			goto err;
		ctx->dec = dec;
		ctx->state = DELTA_STATE_WF_STREAMINFO;
	}

	/*
	 * first buffer should contain stream header,
	 * decode it to get the infos related to stream
	 * such as width, height, dpb, ...
	 */
	vbuf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	if (!vbuf) {
		dev_err(delta->dev, "%s failed to start streaming, no stream header buffer enqueued\n",
			ctx->name);
		ret = -EINVAL;
		goto err;
	}
	au = to_au(vbuf);
	au->size = vb2_get_plane_payload(&vbuf->vb2_buf, 0);
	au->dts = vbuf->vb2_buf.timestamp;

	delta_push_dts(ctx, au->dts);

	/* dump access unit */
	dump_au(ctx, au);

	/* decode this access unit */
	ret = call_dec_op(dec, decode, ctx, au);
	if (ret) {
		dev_err(delta->dev, "%s failed to start streaming, header decoding failed (%d)\n",
			ctx->name, ret);
		goto err;
	}

	ret = call_dec_op(dec, get_streaminfo, ctx, streaminfo);
	if (ret) {
		dev_dbg_ratelimited(delta->dev,
				    "%s failed to start streaming, valid stream header not yet decoded\n",
				    ctx->name);
		goto err;
	}
	ctx->flags |= DELTA_FLAG_STREAMINFO;

	ret = call_dec_op(dec, get_frameinfo, ctx, frameinfo);
	if (ret)
		goto err;
	ctx->flags |= DELTA_FLAG_FRAMEINFO;

	ctx->state = DELTA_STATE_READY;

	dev_dbg(delta->dev, "%s %s => %s\n", ctx->name,
		delta_streaminfo_str(streaminfo, str1, sizeof(str1)),
		delta_frameinfo_str(frameinfo, str2, sizeof(str2)));

	delta_au_done(ctx, au, ret);
	return 0;

err:
	/*
	 * return all buffers to vb2 in QUEUED state.
	 * This will give ownership back to userspace
	 */
	if (vbuf)
		v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_QUEUED);

	while ((vbuf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx)))
		v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_QUEUED);
	return ret;
}